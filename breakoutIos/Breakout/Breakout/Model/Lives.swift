//
//  Lives.swift
//  Breakout
//
//  Created by Sonya Hedider on 14.08.19.
//  Copyright © 2019 Hochschule Darmstadt. All rights reserved.
//

import Foundation
import SpriteKit


class Lives: SKLabelNode{
    
    var LabelOffsetX: CGFloat
    var LabelOffsetY: CGFloat
    var Labelwidth: CGFloat
    var CountLives : Int
    
    init(ToScene view: GameScene) {
        LabelOffsetX = CGFloat()
        LabelOffsetY = CGFloat()
        Labelwidth = CGFloat()
        CountLives = 5
        
        super.init()
        
        
        
        self.name = "Hearts"
        self.text = ""
        self.Labelwidth = 0
        for i in 0..<CountLives{
            self.text = self.text! + "❤️"
            if i == 0{
                self.LabelOffsetX = abs(self.frame.maxX - self.frame.minX)
                self.LabelOffsetY = self.frame.maxY - self.frame.minY
            }
            self.Labelwidth += self.LabelOffsetX
        }
        
        self.horizontalAlignmentMode = .left
        self.position = CGPoint(x: view.SceneEngine.screenorg.minX, y: view.SceneEngine.screenorg.maxY - self.LabelOffsetY)
        
        
        
        
    }
    
    

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
}
