/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GlutObjparent.h
 * Author: arous
 *
 * Created on 6. Mai 2018, 13:23
 */

#ifndef GLUTOBJPARENT_H
#define GLUTOBJPARENT_H

class GlutObjparent {
public:
    GlutObjparent();
    GlutObjparent(const GlutObjparent& orig);
    virtual ~GlutObjparent();
    
        virtual void animate(double value) = 0;
	virtual void renderScene() = 0;
	virtual void keyboardKeys(unsigned char key, int x, int y);
        
        
       
        
private:

};

#endif /* GLUTOBJPARENT_H */

