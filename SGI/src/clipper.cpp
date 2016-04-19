#include "clipper.hpp"

Clipper::Clipper() {}
Clipper::~Clipper() {}

bool Clipper::isOutOfRange(Coordinate coord) {
	return fabs(coord._x) > 1 || fabs(coord._y) > 1;
}

vector<Coordinate> Clipper::clipPoint(Coordinate coord) {
	if (isOutOfRange(coord))
		return vector<Coordinate>();

	return {coord};
}

unsigned int Clipper::regionCodeOf(Coordinate coord) {
	unsigned int code = 0;

	//Using bitwise operators to represent region code.
	code = (coord._y > SCN_MAX) ? (code | UP) : code;
	code = (coord._y < SCN_MIN) ? (code | DOWN) : code;
	code = (coord._x > SCN_MAX) ? (code | RIGHT) : code;
	code = (coord._x < SCN_MIN) ? (code | LEFT) : code;

	return code;
}

vector<Coordinate> Clipper::cohenSutherland(vector<Coordinate> coords) {
	unsigned int rcBegin = regionCodeOf(coords[0]);
	unsigned int rcEnd = regionCodeOf(coords[1]);

	bool insideWindow = !rcBegin && !rcEnd;
	if (insideWindow) 
		return coords;

	bool partiallyInside = (rcBegin != rcEnd) && ( !(rcBegin & rcEnd) );
	if (partiallyInside)
		return applyCohenSutherland(coords, {rcBegin, rcEnd});
	
	return vector<Coordinate>();
}

vector<Coordinate> Clipper::applyCohenSutherland(vector<Coordinate> coords, vector<unsigned int> regionCodes) {
	double m = (coords[1]._y - coords[0]._y) / (coords[1]._x - coords[0]._x);

	vector<Coordinate> clippedCoords;
	double x,y;

	for (int i = 0; i < coords.size(); ++i) {

		if (regionCodes[i] & LEFT) {
			y = m * (SCN_MIN - coords[i]._x) + coords[i]._y;
			clippedCoords.push_back( Coordinate(SCN_MIN, y) );

			continue;
		}
		if (regionCodes[i] & RIGHT) {
			y = m * (SCN_MAX - coords[i]._x) + coords[i]._y;
			clippedCoords.push_back( Coordinate(SCN_MAX, y) );

			continue;
		}
		if (regionCodes[i] & UP) {
			x = coords[i]._x + 1 / m * (SCN_MAX - coords[i]._y);
			clippedCoords.push_back( Coordinate(x, SCN_MAX) );

			continue;
		}
		if (regionCodes[i] & DOWN) {
			x = coords[i]._x + 1 / m * (SCN_MIN - coords[i]._y);
			clippedCoords.push_back( Coordinate(x, SCN_MIN) );

			continue;
		}

		clippedCoords.push_back(coords[i]);
	}

	return clippedCoords;
}

vector<Coordinate> Clipper::liangBarsky(vector<Coordinate> coords) {
	vector<Coordinate> clippedCoords;

	double dx = coords[1]._x - coords[0]._x;
	double dy = coords[1]._y - coords[0]._y;

	vector<double> p = {-dx, dx, -dy, dy};
	vector<double> q = {coords[0]._x - SCN_MIN,
		SCN_MAX - coords[0]._x,
		coords[0]._y - SCN_MIN,
		SCN_MAX - coords[0]._y};

	bool outsideWindow = (!p[0] && q[0] < 0) || (!p[2] && q[2] < 0) ||
						(!p[1] && q[1] < 0) || (!p[3] && q[3] < 0);

	if (outsideWindow)
		return vector<Coordinate>();

	double x, y;
	vector<double> coefs = calculateCoeficients(p, q);

	if (coefs[0] > coefs[1])
		return vector<Coordinate>();
	
	if (coefs[0] > 0) {
		x = coords[0]._x + coefs[0] * dx;
		y = coords[0]._y + coefs[0] * dy;

		clippedCoords.push_back( Coordinate(x,y) );
	} else {
		clippedCoords.push_back( coords[0] );
	}

	if (coefs[1] < 1) {
		x = coords[0]._x + coefs[1] * dx;
		y = coords[0]._y + coefs[1] * dy;

		clippedCoords.push_back( Coordinate(x,y) );
	} else {
		clippedCoords.push_back( coords[1] );
	}

	return clippedCoords;
}

vector<Coordinate> Clipper::weilerAtherton(vector<Coordinate> objectCoords) {
	list<ClippingPoint> object, clip, gettingIn, final;
	list<ClippingPoint>::iterator currentObjVertex, nextObjectVertex, currentWindowVertex, nextWindowVertex, iter;
	vector<Coordinate> currentObjLine, currentWindowLine;
	Coordinate intersection;
	list<ClippingPoint>* container;

	vector<Coordinate> windowCoords = {Coordinate(-1,1), Coordinate(1,1), Coordinate(1,-1), Coordinate(-1,-1)};

	for(Coordinate vertex : objectCoords) {
		object.push_back(ClippingPoint(vertex));
	}

	for(Coordinate vertex : windowCoords) {
		clip.push_back(ClippingPoint(vertex));
	}

	for(currentObjVertex = object.begin(); currentObjVertex != object.end(); currentObjVertex++) {

		if(!currentObjVertex->isArtificial()) {
			nextObjectVertex = next(currentObjVertex, 1);
			while(nextObjectVertex->isArtificial()) {
				nextObjectVertex = next(nextObjectVertex, 1);
			}

			currentObjLine = {Coordinate(currentObjVertex->coord()._x, currentObjVertex->coord()._y), 
							  Coordinate(nextObjectVertex->coord()._x, nextObjectVertex->coord()._y)};

			// FIXME: Problema com pontos fora que cruzam a window.
			if(isOutOfRange((*currentObjVertex).coord()) != isOutOfRange((*nextObjectVertex).coord())) {
				for(currentWindowVertex = clip.begin(); currentWindowVertex != clip.end(); currentWindowVertex++) {
					if(!currentWindowVertex->isArtificial()) {
						nextWindowVertex = next(currentWindowVertex, 1);
						while(nextWindowVertex->isArtificial()) {
							nextWindowVertex = next(nextWindowVertex, 1);
						}

						currentWindowLine = {Coordinate(currentWindowVertex->coord()._x, currentWindowVertex->coord()._y), 
											 Coordinate(nextWindowVertex->coord()._x, nextWindowVertex->coord()._y)};
						
						if(hasIntersection(currentObjLine, currentWindowLine, intersection)) {
							ClippingPoint point = ClippingPoint(intersection, true);

							object.insert(nextObjectVertex, point);
							clip.insert(nextWindowVertex, point);

							if(isOutOfRange(currentObjLine[0]) && !isOutOfRange(currentObjLine[1])) {
								gettingIn.push_back(point);
							}
						}
					}								
				}
			}
		}
	}

	// TODO: Como lidar com polígonos que viram dois?
	bool objectCompleted = false;
	bool firstIterationOnList;

	for(iter = gettingIn.begin(); iter != gettingIn.end(); iter++) {
		ClippingPoint referenceObject = *iter;	
		container = &object;

		while(!objectCompleted) {
			firstIterationOnList = true;

			for(currentObjVertex = getIterator(referenceObject, container); currentObjVertex != container->end(); currentObjVertex++) {
				if(firstIterationOnList) {
					final.push_back(*currentObjVertex);
					firstIterationOnList = false;
				} else {
					if(currentObjVertex->isArtificial()) {
						if(container == &object)
							container = &clip;
						else
							container = &object;

						// if(find(begin(final), end(final), currentObjVertex) != end(final))
							// objectCompleted = true;

						referenceObject = *currentObjVertex;
						break;
					} else {
						final.push_back(ClippingPoint(*currentObjVertex));
					}
				}

				if(next(currentObjVertex, 1) == container->end())
					currentObjVertex = container->begin();
			}
		}
	}

	// Printing
	int i = 1;
	for(currentObjVertex = object.begin(); currentObjVertex != object.end(); currentObjVertex++) {
		cout << "V#" << i << " (" << currentObjVertex->coord()._x << ", " << currentObjVertex->coord()._y << ")" << endl;
		i++;
	}

	cout << endl;

	i = 1;
	for(currentWindowVertex = clip.begin(); currentWindowVertex != clip.end(); currentWindowVertex++) {
		cout << "W#" << i << " (" << currentWindowVertex->coord()._x << ", " << currentWindowVertex->coord()._y << ")" << endl;
		i++;
	}

	cout << endl;

	for(currentWindowVertex = gettingIn.begin(); currentWindowVertex != gettingIn.end(); currentWindowVertex++) {
		cout << "GI#" << " (" << currentWindowVertex->coord()._x << ", " << currentWindowVertex->coord()._y << ")" << endl;
	}

	return objectCoords;
}

vector<double> Clipper::calculateCoeficients(vector<double> p, vector<double> q) {
	vector<double> coefs;

	//Calculo dos valores para coordenada 1
	double r1 = (p[0] < 0) ? (q[0] / p[0]) : (q[1] / p[1]);
	double r2 = (p[2] < 0) ? (q[2] / p[2]) : (q[3] / p[3]);

	r1 = (!isfinite(r1)) ? 0.0 : r1;
	r2 = (!isfinite(r2)) ? 0.0 : r2;

	coefs.push_back( max(0.0, max(r1,r2)) );

	//Calculo dos valores para coordenada 2
	r1 = (p[1] < 0) ? (q[0] / p[0]) : (q[1] / p[1]);
	r2 = (p[3] < 0) ? (q[2] / p[2]) : (q[3] / p[3]);

	r1 = (!isfinite(r1)) ? 1.0 : r1;
	r2 = (!isfinite(r2)) ? 1.0 : r2;

	coefs.push_back( min(1.0, min(r1,r2)) );	

	return coefs;	
}

bool Clipper::hasIntersection(vector<Coordinate> firstLine, vector<Coordinate> secondLine, 
							  Coordinate &intersection) {
	Coordinate a = Coordinate(firstLine[1]._x - firstLine[0]._x, firstLine[1]._y - firstLine[0]._y);
	Coordinate b = Coordinate(secondLine[1]._x - secondLine[0]._x, secondLine[1]._y - secondLine[0]._y);

	double f = a.perpDotProduct(b);

	if(!f)
		return false;
	
	Coordinate c = Coordinate(secondLine[1]._x - firstLine[1]._x, secondLine[1]._y - firstLine[1]._y);
	
	double aa = a.perpDotProduct(c);
	double bb = b.perpDotProduct(c);

	if(f < 0) {
		if(aa > 0) return false;
		if(bb > 0) return false;
		if(aa < f) return false;
		if(bb < f) return false;
	} else {
		if(aa < 0) return false;
		if(bb < 0) return false;
		if(aa > f) return false;
		if(bb > f) return false;
	}

	double coef = 1.0 - (aa / f);
	intersection = Coordinate(((secondLine[1]._x - secondLine[0]._x) * coef) + secondLine[0]._x, 
							  ((secondLine[1]._y - secondLine[0]._y) * coef) + secondLine[0]._y);

	return true;
}

list<ClippingPoint>::iterator Clipper::getIterator(ClippingPoint object, list<ClippingPoint>* container) {
	list<ClippingPoint>::iterator iter;
	for(iter = container->begin(); iter != container->end(); iter++) {
		if((ClippingPoint*) iter->equals(object))
			return iter;
	}

	return iter;
}