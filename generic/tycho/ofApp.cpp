#include "ofApp.h"
#include "tycho_colors.h"

//--------------------------------------------------------------
void ofApp::setup(){
    /* Set the Background to Tycho's album cover background */
    ofBackgroundHex(bg);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    /* Set our triangle size and parallelogram width */
    const float tri_side = 200;
    const float par_width = 20;
    
    /* Calculate half the height which equals the distance
     * from the center of the circle to any of it's vertices
     * sqrt(hypotenuse^2 - adjacent^2)
     */
    const float tri_hheight = sqrt(tri_side * tri_side - tri_side / 2 * tri_side / 2) / 2.0;
    
    /* Calculate half the width of our Tycho shape so we can center it */
    const float tycho_width = (par_width * (NUM_TYCHO_COLORS - 1)) / 2.0;
    
    /* Create the vertices of our triangle
     * using the distance from the center
     * we calculated earlier
     */
    ofPoint top  = ofPoint(0, -tri_hheight);
    ofPoint left = ofPoint(-tri_hheight, tri_hheight);
    ofPoint right = ofPoint(tri_hheight, tri_hheight);

    /* Store the coordinate system and styling
     * we had before this point
     */
    ofPushStyle();
    ofPushMatrix();
    {
        /* Shift our drawing location to
         * the middle of the screen minus
         * half the width of the Tycho shape
         * so that it is centered
         */
        ofTranslate(ofGetWidth() / 2. - tycho_width,
                    ofGetHeight() / 2.);
        
        /* Set the triangle to the first color in our array and draw it */
        ofSetHexColor(colors[0]);
        ofTriangle(left, top, right);
    
        /* Translate to top of triangle for parallelograms */
        ofPushMatrix();
        {
            /* Draw respective to the top vertex of the triangle */
            ofTranslate(top.x, top.y);
        
            /* The height of the parallelogram is the same for each parallelogram */
            const float par_h = tri_hheight * 2.;
        
            /* The x values will be updated each time
             * we draw them so define them outside the loop
             *(x1,y1)------(x2,y2)
             * \             \
             *  \             \
             *   \--par_width--\
             *    \             \
             *     \             \
             *     (x3,y3)-------(x4,y4)  */
            float x1, x2, x3, x4;
        
            /* Start at -20.0 so that our first shift makes x1 = 0.0 */
            x1 = 0;
            x2 = par_width;

            /* x3 is at the right vertex so shift it half the triangle width */
            x3 = tri_hheight;
            x4 = x3 + par_width;
        
            for(int i = 0; i < NUM_TYCHO_COLORS - 1; ++i)
            {
                /* Use the next Tycho color */
                ofSetHexColor(colors[i+1]);

                /* Draw the parallelogram using the vertices we calculated */
                ofBeginShape();
                    ofVertex(x1, 0.);
                    ofVertex(x2, 0.);
                    ofVertex(x4, par_h);
                    ofVertex(x3, par_h);
                ofEndShape();
                
                /* Shift all the x vertices by our parallelogram width */
                x1 += par_width;
                x2 += par_width;
                x3 += par_width;
                x4 += par_width;
            }
        }
        /* Pop our top triangle translation */
        ofPopMatrix();
    }
    /* Pop our centered translation and our custom Tycho styling */
    ofPopMatrix();
    ofPopStyle();

    
    /* Draw Dots */
    /* Centered vertically  */
    ofPushStyle();
    ofPushMatrix();
    {
        /* Store the dimensions of the rectangular
         * space underneath the triangle shape. I'll
         * call it 'footer'
         */
        const float footer_h = ofGetHeight() /2. - tri_hheight;
        const float footer_w = ofGetWidth();
        const float dot_rad = 2.; // 2px radius
        const float dot_space = 8.;
        /* The width of the dot structure is based on diameter,
         * the number of dots, and the empty dot-size space
         * between each dot (7 dots 6 spaces = 13)
         * vertically there are (2 dots and 1 space = 3)
         */
        const float dots_w = dot_rad * 2. * 13.;
        const float dots_h = dot_rad * 2. * 3.;

        /* Draw relative to ... */
        ofTranslate((ofGetWidth() / 2.) - (dots_w / 2.),
                   ((ofGetHeight() / 2.) + tri_hheight) + (footer_h / 2.) - (dots_h / 2.));

        /* Use the Triangle's color to draw */
        ofSetHexColor(colors[0]);
        
        /* Draw dots with spacing */
        for (int i = 0; i < TYCHO_DOTS_ROWS; ++i) {
            for(int j = 0; j < TYCHO_DOTS_COLS; j++)
            {
                /* dots are stored as booleans.  true means draw, false means don't draw */
                if(dots[i][j])
                {
                    /* Multiply the spacing by our index to get the correct x/y shifting */
                    ofCircle(dot_space * j + 1 * dot_rad, dot_space * i + 1, dot_rad);
                }
            }
        }
    }
    /* Pop the dots translation and style */
    ofPopMatrix();
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
