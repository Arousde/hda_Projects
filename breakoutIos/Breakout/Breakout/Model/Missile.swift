//
//  missile.swift
//  Breakout
//
//  Created by Arous Oussema on 27.08.19.
//  Copyright © 2019 Hochschule Darmstadt. All rights reserved.
//

import Foundation


import SpriteKit
class Missile: SKSpriteNode {
    
    init(View: GameScene) {
        let texture = SKTexture(imageNamed: "bomb")
        super.init(texture: texture, color: .clear , size: texture.size())
        self.name = "bomb"
        
        self.zPosition = 5
        self.position = CGPoint(x: View.SceneEngine.paddleController.paddleNode.position.x  ,y: View.SceneEngine.paddleController.paddleNode.position.y + 10)
        self.setScale(0.3)
        
        self.physicsBody = SKPhysicsBody(rectangleOf: self.frame.size)
        self.physicsBody?.isDynamic = true
        self.physicsBody?.categoryBitMask = PhysicsCategory.MissileCategory
        self.physicsBody?.contactTestBitMask = PhysicsCategory.BrickCategory
        self.physicsBody?.collisionBitMask = PhysicsCategory.BrickCategory
        
        View.addChild(self)
        self.physicsBody?.applyImpulse(CGVector(dx: 0, dy: 20))
        
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
}
