#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh.clear();

	float span = 0.5;
	for (float noise_param = 0; noise_param < 1.1; noise_param += 0.1) {

		float noise_seed = ofRandom(10000);

		for (float x = 20; x <= 700; x += span) {

			for (float y = 20; y <= 700; y += span) {

				float noise_value = ofNoise(noise_seed + ofGetFrameNum() * 0.0025, x * 0.008, y * 0.008, ofGetFrameNum() * 0.0025);
				if (noise_value >= noise_param - 0.005 && noise_value <= noise_param + 0.005) {

					this->mesh.addVertex(glm::vec3(x, y, 0));
					this->mesh.addVertex(glm::vec3(x + span, y, 0));
					this->mesh.addVertex(glm::vec3(x + span, y + span, 0));
					this->mesh.addVertex(glm::vec3(x, y + span, 0));

					this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 4); this->mesh.addIndex(this->mesh.getNumVertices() - 3);
					this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 2); this->mesh.addIndex(this->mesh.getNumVertices() - 3);

					ofColor color;
					color.setHsb(ofMap(noise_param, -0.005, 1.005, 0, 255), 130, 255);
					for (int i = 0; i < 4; i++) {

						this->mesh.addColor(color);
					}
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->mesh.draw();

	/*
	int start = 1;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}