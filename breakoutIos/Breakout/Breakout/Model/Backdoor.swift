//
//  BAckdoor.swift
//  Breakout
//
//  Created by Arous Oussema on 25.08.19.
//  Copyright © 2019 Hochschule Darmstadt. All rights reserved.
//

import Foundation

import SpriteKit
class Backdoor: SKSpriteNode {
    
    
    
    init(View: GameScene) {
        
        let texture = SKTexture(imageNamed: "backdoor")
        super.init(texture: texture, color: .clear , size: texture.size())
        self.name = "baackdoor"
        self.zPosition = 10
        self.position = CGPoint(x:View.frame.maxX - 10,y:View.frame.minY + 95)
        self.setScale(0.7)
        
        var bodysize = self.size
        bodysize.width = 5
        self.physicsBody = SKPhysicsBody(rectangleOf: bodysize)
        self.physicsBody!.isDynamic = true
        self.physicsBody!.categoryBitMask = PhysicsCategory.Backdoor
        //self.physicsBody!.contactTestBitMask = PhysicsCategory.PaddleCategory
       self.physicsBody!.collisionBitMask = 0
        
        View.addChild(self)
        
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
}
