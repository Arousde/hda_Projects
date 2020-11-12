
import SpriteKit
import GameplayKit
import AVFoundation


extension GameScene: SKPhysicsContactDelegate {
    
    
    func didBegin(_ contact: SKPhysicsContact) {
        // 1
        var firstBody: SKPhysicsBody
        var secondBody: SKPhysicsBody
        if contact.bodyA.categoryBitMask < contact.bodyB.categoryBitMask {
            firstBody = contact.bodyA
            secondBody = contact.bodyB
        } else {
            firstBody = contact.bodyB
            secondBody = contact.bodyA
        }
        
        if firstBody.categoryBitMask == PhysicsCategory.BallCategory && secondBody.categoryBitMask == PhysicsCategory.BottomCategory{
            
            if  let b = firstBody.node as? Projectile {
                let ball = b
                SceneEngine.livesController!.liveLoss(ToScene: self, from: SceneEngine, withBall: ball)
                run(SceneEngine.gameController.gameConfig.losesound)
            }
            
        }
        
        
        if firstBody.categoryBitMask == PhysicsCategory.BallCategory && secondBody.categoryBitMask == PhysicsCategory.BrickCategory {
            
            
            if let testbrick = secondBody.node as? Brick {
                let brick = testbrick
                SceneEngine.scoreController.hitBrick(brick: brick, ToScene: self, from: SceneEngine)
                
            }
        }
        
        if firstBody.categoryBitMask == PhysicsCategory.BallCategory && secondBody.categoryBitMask == PhysicsCategory.PaddleCategory {
            run(SceneEngine.gameController.gameConfig.wallsound)
            if let paddle = secondBody.node as? Paddle {
                if SceneEngine.paddleController.violetMagnetPaddle == paddle.texture{
                    if  let b = firstBody.node as? Projectile {
                        b.physicsBody?.isDynamic = false
                        
                        
                    }
                }
                
            }
            
        }
        
        
        if firstBody.categoryBitMask == PhysicsCategory.PaddleCategory && secondBody.categoryBitMask == PhysicsCategory.PowerUp {
            if let Power = secondBody.node as? PowerUp {
                SceneEngine.bricksBuilder.PowerupCntrl.eat(ToScene: self, Power: Power)
                Power.removeFromParent()
            }
            
        }
        
        if firstBody.categoryBitMask == PhysicsCategory.BottomCategory && secondBody.categoryBitMask == PhysicsCategory.PowerUp {
            if  let power = secondBody.node as? PowerUp{
                power.removeFromParent()
            }
        }
        

        if firstBody.categoryBitMask == PhysicsCategory.PaddleCategory && secondBody.categoryBitMask == PhysicsCategory.Backdoor{
            if (secondBody.node as? Backdoor) != nil {
                SceneEngine.bricksBuilder.PowerupCntrl.PowerGoNextLevel(view: self)
            }
            
            
        }
        
        
        //LASER POWERUP 
        
        if firstBody.categoryBitMask == PhysicsCategory.BrickCategory && secondBody.categoryBitMask == PhysicsCategory.LaserCategory{
            if let brick = firstBody.node as? Brick {
                SceneEngine.scoreController.hitBrick(brick: brick, ToScene: self, from: SceneEngine)
            }
            if let laser = secondBody.node as? Laser {
                laser.removeFromParent()
            }
        }
        if firstBody.categoryBitMask == PhysicsCategory.BorderCategory && secondBody.categoryBitMask == PhysicsCategory.LaserCategory{
            if let laser = secondBody.node as? Laser {
                laser.removeFromParent()
            }
        }
        
        
        // Missile POwerUp
        if firstBody.categoryBitMask == PhysicsCategory.BrickCategory && secondBody.categoryBitMask == PhysicsCategory.MissileCategory{
            if let brick = firstBody.node as? Brick {
                SceneEngine.scoreController.hitWallsBrick(brick: brick, ToScene: self, from: SceneEngine)
            }
            if let missile = secondBody.node as? Missile {
                missile.removeFromParent()
            }
        }
        
        if firstBody.categoryBitMask == PhysicsCategory.BorderCategory && secondBody.categoryBitMask == PhysicsCategory.MissileCategory{
            if let missile = secondBody.node as? Missile {
                missile.removeFromParent()
            }
        }
        
    }
        
    
    
    func didEnd(_ contact: SKPhysicsContact) {
        // initialize
        var firstBody: SKPhysicsBody
        var secondBody: SKPhysicsBody
        if contact.bodyA.categoryBitMask < contact.bodyB.categoryBitMask {
            firstBody = contact.bodyA
            secondBody = contact.bodyB
        } else {
            firstBody = contact.bodyB
            secondBody = contact.bodyA
        }
        
        // do something
        
        if firstBody.categoryBitMask == PhysicsCategory.BallCategory && secondBody.categoryBitMask == PhysicsCategory.BorderCategory {
            
            run(SceneEngine.gameController.gameConfig.wallsound)
            
            
        }
        
       
        
    }
    
}




