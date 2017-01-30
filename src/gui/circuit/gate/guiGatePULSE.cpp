
#include "guiGatePULSE.h"
#include <sstream>
#include "../../thread/Message.h"

using namespace std;

guiGatePULSE::guiGatePULSE() : guiGate() {

	// Set the default CLICK box:
	// Format is: "minx miny maxx maxy"
	setGUIParam("CLICK_BOX", "-0.76,-0.76,0.76,0.76");

	// Default to single pulse width:
	setGUIParam("PULSE_WIDTH", "1");
};

// Send a pulse message to the logic core whenever the gate is
// clicked on:
Message_SET_GATE_PARAM* guiGatePULSE::checkClick(GLfloat x, GLfloat y) {
	klsBBox toggleButton;

	// Get the size of the CLICK square from the parameters:
	string clickBox = getGUIParam("CLICK_BOX");
	istringstream iss(clickBox);
	GLdouble minx = -0.5;
	GLdouble miny = -0.5;
	GLdouble maxx = 0.5;
	GLdouble maxy = 0.5;
	char dump;
	iss >> minx >> dump >> miny >> dump >> maxx >> dump >> maxy;

	toggleButton.addPoint(modelToWorld(GLPoint2f(minx, miny)));
	toggleButton.addPoint(modelToWorld(GLPoint2f(minx, maxy)));
	toggleButton.addPoint(modelToWorld(GLPoint2f(maxx, miny)));
	toggleButton.addPoint(modelToWorld(GLPoint2f(maxx, maxy)));

	if (toggleButton.contains(GLPoint2f(x, y))) {
		/*		ostringstream oss;
		oss << "SET GATE ID " << getID() << " PARAMETER PULSE " << getGUIParam("PULSE_WIDTH"); */
		return new Message_SET_GATE_PARAM(getID(), "PULSE", getGUIParam("PULSE_WIDTH"));
	}
	else return NULL;
}