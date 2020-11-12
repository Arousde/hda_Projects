//
//  SceneEngine.swift
//  Breakout
//
//  Created by Arous Oussema on 13.08.19.
//  Copyright © 2019 Hochschule Darmstadt. All rights reserved.
//

import Foundation
import SpriteKit
import AVFoundation



class ScEngine {
    
    // for testing ball speed
    var Ballspeed: Int?
    
    var isFingerOnPaddle = false
    var paddleController = PaddleController()
    var Ball: Projectile?
    let scoreController = ScoreController()
    var bricksBuilder = BricksBuilder()
    var gameController = GameController()
    // this to check if the ball is in its initial position above the paddle
    var firsttouch = true
    var paused = false
    var inGame = false
    var screenorg = CGRect()
    var livesController : LivesController?

    var ballctrl = BallController()


    
    
    public func ballWallbehaveOnRightLeft(ToScene view: GameScene, ball: Projectile){}
    
    public func ballWallbehaveOnTop(ToScene view: GameScene, ball: Projectile){}
    
    public func ballWallbehaveOnPaddle(ToScene view: GameScene, ball: Projectile){}
    


    
    public func addHearts(){
        if scoreController.scoreCounter >= 100{
            scoreController.scoreCounter = 0
            livesController!.addLive()
        }
    }
 
    public func makeNextlevel(ToScene view: GameScene) {
       PowerUpsController.CancelAllJobsTimers()
        
        PowerUpsController.BAllIndexName = 0
        Projectile.resetBallvelocity()
        bricksBuilder.addallBlocks(ToScene: view)
        gameController.gameState.next.removeFromParent()
        gameController.gameState.Labelnext.removeFromParent()
        gameController.gameConfig.background.zPosition = -2
        paddleController = PaddleController()
        paddleController.showPaddle(ToScene: view)
//        view.addChild(view.SceneEngine.paddleController.paddleNode)
        Ball = Projectile(BallTexture:Projectile.defaultBall, ToScene: view)
        view.addChild(Ball!)
        firsttouch = true
        
        view.run(gameController.gameConfig.startsound)
    }
    

    
    func ScenePhysiscs(ToScene view: GameScene){
        //    let border = CGRect(x: frame.origin.x, y: frame.origin.y, width: frame.size.width, height: frame.size.height)

        let borderBody = SKPhysicsBody(edgeLoopFrom: view.frame)
        borderBody.friction = 0
        view.physicsBody = borderBody
        view.physicsBody?.restitution = 1
        //Ball contact
        view.physicsBody?.categoryBitMask = PhysicsCategory.BorderCategory
        view.physicsBody?.contactTestBitMask = PhysicsCategory.BallCategory
        
        view.physicsWorld.gravity = CGVector(dx: 0.0, dy: 0.0)
        view.physicsWorld.contactDelegate = view as SKPhysicsContactDelegate
        
        //        // add top
        //        let TopRect = CGRect(x: frame.origin.x, y: frame.maxY, width: frame.size.width, height: frame.height)
        //        let top = SKNode()
        //        top.physicsBody = SKPhysicsBody(edgeLoopFrom: TopRect)
        //        top.physicsBody?.categoryBitMask = PhysicsCategory.TopCategory
        //        top.physicsBody?.contactTestBitMask = PhysicsCategory.BallCategory
        //        top.physicsBody?.friction = 0
        //        top.physicsBody?.restitution = 1
        //        addChild(top)
        //
                // add left
//                let leftRect = CGRect(x: view.frame.maxX, y: view.frame.origin.y, width: 0.0, height: view.frame.height)
//                let left = SKNode()
//                left.physicsBody = SKPhysicsBody(edgeLoopFrom: leftRect)
//                left.physicsBody?.categoryBitMask = PhysicsCategory.leftCategory
//                left.physicsBody?.contactTestBitMask = PhysicsCategory.PaddleCategory
//                left.physicsBody?.friction = 0
//                left.physicsBody?.restitution = 1
//                view.addChild(left)
//
                // add right
//                let rightRect = CGRect(x: view.frame.minX, y: view.frame.origin.y, width: 0.0, height: view.frame.height)
//                let right = SKNode()
//                right.physicsBody = SKPhysicsBody(edgeLoopFrom: rightRect)
//                right.physicsBody?.categoryBitMask = PhysicsCategory.rightCategory
//                right.physicsBody?.contactTestBitMask = PhysicsCategory.BallCategory
//                right.physicsBody?.friction = 0
//                right.physicsBody?.restitution = 1
//                view.addChild(right)
        
        
    }
    
    public func playFirstTime(ToScene view: GameScene) {
        screenorg = CGRect(x: view.frame.origin.x, y: view.frame.origin.y, width: view.frame.size.width, height: view.frame.size.height)
        livesController = LivesController(ToScene: view)
        ScenePhysiscs(ToScene: view)
        
        gameController.gameConfig.background.zPosition = -2
        gameController.gameState.play.removeFromParent()
        gameController.gameState.LabelPlay.removeFromParent()
        paddleController = PaddleController()
        paddleController.showPaddle(ToScene: view)
        Ball = Projectile(BallTexture: Projectile.defaultBall, ToScene: view)
        view.addChild(Ball!)
                
        
        livesController!.showLives(ToScene: view)
        gameController.makeBottom(ToScene: view, paddle: paddleController.paddleNode)
        scoreController.schowScore(ToScene: view, from: self)
        gameController.showGoBack(ToScene: view)
        gameController.showPause(ToScene: view)
        gameController.showLittlereplay(ToScene: view)
        bricksBuilder.addallBlocks(ToScene: view)
        view.run(gameController.gameConfig.startsound)
        
                Projectile.resetBallvelocity()
                ballctrl = BallController()
                ballctrl.increaseBallSpeedWithTime()
               PowerUpsController.CancelAllJobsTimers()

    }
    public func playAfterGameOver(ToScene view: GameScene){
        
        ScenePhysiscs(ToScene: view)
        gameController.deleteGameOverView(WithImage: "background" , ToScene: view)
        
        PowerUpsController.BAllIndexName = 0
        paddleController = PaddleController()
        paddleController.showPaddle(ToScene: view)
        Ball = Projectile(BallTexture: Projectile.defaultBall, ToScene: view)
        view.addChild(Ball!)

        
        
        livesController!.showLives(ToScene: view)
        gameController.makeBottom(ToScene: view, paddle: paddleController.paddleNode)
        scoreController.schowScore(ToScene: view, from: self)
        gameController.showGoBack(ToScene: view)
        gameController.showPause(ToScene: view)
        gameController.showLittlereplay(ToScene: view)
        bricksBuilder.addallBlocks(ToScene: view)
        view.run(gameController.gameConfig.startsound)
        PowerUpsController.CancelAllJobsTimers()
        Projectile.resetBallvelocity()

    }
    
    public func paddleTouch(){
        if firsttouch {
            //   print(Ball.physicsBody!.velocity)
            firsttouch = false
        }
        isFingerOnPaddle = true
    }
    
    
    public func onPlayTouched(ToScene view: GameScene) {
        
        playFirstTime(ToScene: view)
        gameController.gameConfig.audioPlayer.stop()
        view.run(gameController.gameConfig.startsound)
    }
    
    public func gameOver(at touchLocation: CGPoint, ToScene view: GameScene) {
        view.setPlayFlagsFalse()
                view.removeAllChildren()
        livesController?.resetLives()
                firsttouch = true
        inGame = true
                playAfterGameOver(ToScene: view)
                gameController.gameConfig.audioPlayer.stop()
        
    }
    
}
