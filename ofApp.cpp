#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_MULTIPLY);

	while (this->location_list.size() < 8) {

		auto location = glm::vec2(ofRandom(140, ofGetWidth() - 140), ofRandom(140, ofGetHeight() - 140));
		auto radius = ofRandom(65, 120);
		auto flag = true;
		for (int i = 0; i < this->location_list.size(); i++) {

			if (glm::distance(location, this->location_list[i]) < this->radius_list[i] + radius) {

				flag = false;
				break;
			}
		}

		if (flag) {

			this->location_list.push_back(location);
			this->radius_list.push_back(radius);
		}
	}

	while (this->location_list.size() < 45) {

		auto location = glm::vec2(ofRandom(140, ofGetWidth() - 140), ofRandom(140, ofGetHeight() - 140));
		auto radius = ofRandom(10, 40);
		auto flag = true;
		for (int i = 0; i < this->location_list.size(); i++) {

			if (glm::distance(location, this->location_list[i]) < this->radius_list[i] + radius) {

				flag = false;
				break;
			}
		}

		if (flag) {

			this->location_list.push_back(location);
			this->radius_list.push_back(radius * 1.2);
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofColor color;
	vector<ofColor> color_list;
	vector<int> hex_list = { 0x264653, 0x2a9d8f, 0xe9c46a, 0xf4a261, 0xe76f51 };
	for (auto hex : hex_list) {

		color.setHex(hex);
		color_list.push_back(color);
	}

	for (int i = 0; i < this->location_list.size(); i++) {

		ofPushMatrix();
		ofTranslate(this->location_list[i]);

		for (int k = 0; k < color_list.size(); k++) {

			auto noise_seed_deg = ofRandom(1000);
			auto noise_seed_radius = ofRandom(1000);
			int frame_param = ofRandom(1000);

			vector<glm::vec2> vertices;
			for (int m = 0; m < 15; m++) {

				auto noise_deg = ofMap(ofNoise(noise_seed_deg, (frame_param + ofGetFrameNum() + m) * 0.002), 0, 1, -360, 360);
				auto noise_radius = ofMap(ofNoise(noise_seed_radius, (frame_param + ofGetFrameNum() + m) * 0.02), 0, 1, this->radius_list[i] * -1, this->radius_list[i]);
				vertices.push_back(glm::vec2(noise_radius * cos(noise_deg * DEG_TO_RAD), noise_radius * sin(noise_deg * DEG_TO_RAD)));
			}

			ofSetColor(color_list[k]);
			for (int m = 0; m < 10; m++) {

				ofRotateZ(36);

				ofBeginShape();
				ofVertices(vertices);
				ofEndShape();
			}
		}

		ofPopMatrix();
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}