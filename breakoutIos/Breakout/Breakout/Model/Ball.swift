//
//  Ball.swift
//  Breakout
//
//  Created by Arous Oussema on 15.08.19.
//  Copyright © 2019 Hochschule Darmstadt. All rights reserved.
//

import Foundation
import SpriteKit
class Projectile: SKSpriteNode {
    
    static public   let defaultBall = SKTexture(imageNamed: "ball_silver")
   static public let redBall = SKTexture(imageNamed: "ball_red")
   static public let blueBall = SKTexture(imageNamed: "ball_blue")
  static public  let violetBall = SKTexture(imageNamed: "ball_violet")

    
    public static var BallvelocityDxMax: CGFloat = 200.1
    public static var BallvelocityDxMin: CGFloat = -200.1

    public static var BallvelocityDyMax: CGFloat = 200.1
    public static var BallvelocityDyMin: CGFloat = -200.1

    
    init(BallTexture: SKTexture,ToScene view: GameScene) {
        
        super.init(texture: BallTexture, color: .clear, size: BallTexture.size())
        self.name = "first ball"
        self.setScale(0.04)
        self.zPosition = 6
        let screenorg = CGRect(x:  view.frame.origin.x, y: view.frame.origin.y, width: view.frame.size.width, height: view.frame.size.height)
        self.position = CGPoint(x: 0.0, y: screenorg.minY + 100)
        //physical body
        self.physicsBody = SKPhysicsBody(circleOfRadius: self.size.width / 2 )        
        self.physicsBody!.allowsRotation = true
        self.physicsBody!.friction = 0
        self.physicsBody!.restitution = 1
        self.physicsBody!.linearDamping = 0
        self.physicsBody!.angularDamping = 0
        self.physicsBody!.isDynamic = true
        //Bitmask
        self.physicsBody!.categoryBitMask = PhysicsCategory.BallCategory
        self.physicsBody!.contactTestBitMask = PhysicsCategory.BrickCategory
        self.physicsBody!.collisionBitMask = PhysicsCategory.BrickCategory | PhysicsCategory.BorderCategory | PhysicsCategory.PaddleCategory | PhysicsCategory.BallCategory
            //| PhysicsCategory.Backdoor
       
        
        // Ball.physicsBody!.categoryBitMask = PhysicsCategory.BottomCategory
        // Ball.physicsBody?.contactTestBitMask = PhysicsCategory.PaddleCategory

  //      view.addChild(self)
        
    }
//    override func copy() -> Any {
//        let copy = Projectile(Ballimage: ballimage, ToScene: sCcene!)
//        return copy
//    }
   public func changeImage(BallTexture: SKTexture) {
        self.texture = BallTexture
    }
    
    public func changeImageInTimer (BallTexture: SKTexture) throws {
        self.texture = BallTexture
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    
    public static func resetBallvelocity() {
        Projectile.BallvelocityDxMax = 200.1
        Projectile.BallvelocityDxMin = -200.1
        
        Projectile.BallvelocityDyMax = 200.1
        Projectile.BallvelocityDyMin = -200.1
    }
    
    public func resetBallCollisionInTimer() throws {
    self.physicsBody?.collisionBitMask = PhysicsCategory.BrickCategory | PhysicsCategory.BorderCategory |
        PhysicsCategory.PaddleCategory | PhysicsCategory.BallCategory
        
    }
    
}
