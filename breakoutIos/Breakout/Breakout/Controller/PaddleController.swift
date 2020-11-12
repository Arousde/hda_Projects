//
//  Paddle.swift
//  Breakout
//
//  Created by Sonya Hedider on 14.08.19.
//  Copyright © 2019 Hochschule Darmstadt. All rights reserved.
//

import Foundation
import SpriteKit


class PaddleController {
    var paddleNode: Paddle
    var paddleImage: String
    
    let MissilePaddle = SKTexture(imageNamed: "Missile-paddle")
    let redPaddle = SKTexture(imageNamed: "red-paddle")
    let greyPaddle = SKTexture(imageNamed: "grey-paddle")
    let violetMagnetPaddle = SKTexture(imageNamed: "violet-magnet-paddle")
    
    public static var OriginalPaddleSize =  CGSize()
    init() {
        paddleImage = "grey-paddle"
        paddleNode = Paddle(PaddleImage: paddleImage)

    }
    
    public func genAllData(paddle : SKNode){
        paddleNode.paddleXmin = paddle.frame.minX
        paddleNode.paddleXmax = paddle.frame.maxX
        
        paddleNode.Paddlewidth = paddleNode.paddleXmax * 2
        
        paddleNode.paddleYmin = paddle.frame.minY
        paddleNode.paddleYmax = paddle.frame.maxY
        
        paddleNode.Paddleheight = -(paddleNode.paddleYmin - paddleNode.paddleYmax)
        
        paddleNode.paddleOffsetY = (-paddleNode.paddleYmin - -paddleNode.paddleYmax) - 100
        
        paddleNode.paddleOffsetMin = paddleNode.paddleXmin + 10
        paddleNode.paddleOffsetMax = paddleNode.paddleXmax - 10
    }
    
    
    public func showPaddle(ToScene view: GameScene) {
//        paddleNode.size.width = SKSpriteNode(imageNamed: image).size.width
//        paddleNode.size.height = SKSpriteNode(imageNamed: image).size.height
        paddleNode.setScale(1.7)
        
        paddleNode.zPosition = 6
        paddleNode.name = "paddle"
        let screenorg = CGRect(x:  view.frame.origin.x, y: view.frame.origin.y, width: view.frame.size.width, height: view.frame.size.height)
        paddleNode.position = CGPoint(x: 0, y: screenorg.minY + 80)
        
        genAllData(paddle: paddleNode)
        
        // Body Type > Bounding rectangle not edgeLoopFrom
        var bodysize = paddleNode.size
        bodysize.width += 20
        bodysize.height -= 20

        paddleNode.physicsBody = SKPhysicsBody(rectangleOf: bodysize)
        paddleNode.physicsBody!.friction = 0
        paddleNode.physicsBody!.restitution = 1
        paddleNode.physicsBody!.isDynamic = false
        paddleNode.physicsBody!.categoryBitMask = PhysicsCategory.PaddleCategory
        paddleNode.physicsBody!.contactTestBitMask = PhysicsCategory.BallCategory | PhysicsCategory.Backdoor
//        paddleNode.physicsBody!.collisionBitMask = PhysicsCategory.Backdoor
        for node in view.children{
            if  let paddle = node as? Paddle {
                paddle.removeFromParent()
            }
        }
        PaddleController.OriginalPaddleSize = paddleNode.size
        view.addChild(paddleNode)
        
    }
    
    public func paddleMove(touch: UITouch, ToScene view: GameScene, from SceneEngine: ScEngine){
        
        if SceneEngine.isFingerOnPaddle {
            
            let touchLocation = touch.location(in: view)
            let previousLocation = touch.previousLocation(in: view)
            // always if let to check if object exist
            if let paddle = view.childNode(withName: "paddle")  as? Paddle{
                paddleNode = paddle
                let paddleX = paddleNode.position.x + (touchLocation.x - previousLocation.x)
                let screenorg = CGRect(x:  view.frame.origin.x, y: view.frame.origin.y, width: view.frame.size.width, height: view.frame.size.height)
                if (paddleX + paddleNode.paddleOffsetMin) > screenorg.minX && (paddleX + paddleNode.paddleOffsetMax) < screenorg.maxX{
                    paddleNode.position = CGPoint(x: paddleX, y: paddleNode.position.y)
                    
                    
                    for node in view.children {
                        if let Ball = node as? Projectile {
                            if !Ball.physicsBody!.isDynamic {
                                
                                let paddleX = Ball.position.x + (touchLocation.x - previousLocation.x)
                                let screenorg = CGRect(x:  view.frame.origin.x, y: view.frame.origin.y, width: view.frame.size.width, height: view.frame.size.height)
                                if (paddleX + paddleNode.paddleOffsetMin) > screenorg.minX && (paddleX + paddleNode.paddleOffsetMax) < screenorg.maxX{
                                    Ball.position = CGPoint(x: paddleX, y: Ball.position.y)
                                
                                }
                            }
                        }
                    }
                }
            }
           
            
        }
    }
}
