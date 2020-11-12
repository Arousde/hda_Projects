//
//  PowerUp.swift
//  Breakout
//
//  Created by Arous Oussema on 18.08.19.
//  Copyright © 2019 Hochschule Darmstadt. All rights reserved.
//

import Foundation
import SpriteKit
class PowerUp : SKLabelNode {
    public var power = String()
    public var powertext = String()
    let powerUpSonya = SKLabelNode()

    override init() {
        super.init()
    }
    
     init(fontName: String, Power: String, Powertext: String) {
        

        super.init(fontNamed: fontName)
        self.power = Power
        self.powertext = Powertext
        self.text = Powertext
        self.name = "Power"
        self.fontColor = #colorLiteral(red: 0.5725490451, green: 0, blue: 0.2313725501, alpha: 1)
        
        
        self.zPosition = 5
        self.physicsBody = SKPhysicsBody(rectangleOf: CGSize(width: 20, height: 20))
        
        //  print("ball mass : \(Ball.physicsBody?.mass)")
        self.physicsBody?.isDynamic = true
        //Bitmask
        self.physicsBody?.categoryBitMask = PhysicsCategory.PowerUp
        self.physicsBody?.contactTestBitMask = PhysicsCategory.PaddleCategory | PhysicsCategory.BottomCategory
        self.physicsBody?.collisionBitMask = PhysicsCategory.PaddleCategory | PhysicsCategory.BottomCategory
        
      
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
   
    
    
  
 
}
