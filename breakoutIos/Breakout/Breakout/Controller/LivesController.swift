//
//  Lives.swift
//  Breakout
//
//  Created by Sonya Hedider on 14.08.19.
//  Copyright © 2019 Hochschule Darmstadt. All rights reserved.
//

import Foundation
import SpriteKit


class LivesController{
    
    var Label: Lives
    
    
    init(ToScene view: GameScene) {
        Label = Lives(ToScene: view)
    }
    
    
    public func liveLoss(ToScene view: GameScene,from SceneEngine: ScEngine,withBall Ball: Projectile){
        
       Ball.removeFromParent()
        
        
        for ball in view.children{
            if ball is Projectile {
                return
            }
        }
        SceneEngine.isFingerOnPaddle = false
        SceneEngine.paddleController.paddleNode.removeFromParent()
        
        // Cancel all thing they have to do with ball Ball  powerUps
        Projectile.resetBallvelocity()
        PowerUpsController.CancelAllJobsTimers()
        
        
        

          removeLive()
        
        // save new HighScore
        if Label.CountLives == 0{
            if SceneEngine.scoreController.score > Int(HiScoreReader.HighInt) {
                let newHighScore = SceneEngine.scoreController.score
                HiScoreReader.WriteNewHiScore(Name: "Arous", Hiscore: String(newHighScore))
                HiScoreReader.readHiScore()
            }
           /*end HighScore */
            
            SceneEngine.gameController.gameConfig.background.zPosition = 8
            

            SceneEngine.gameController.gameConfig.audioPlayer.play()
            
            SceneEngine.inGame = false
            view.SceneEngine.gameController.gameState.pauseForViewIScreated = false
            SceneEngine.gameController.showGameOver(ToScene: view)
            
        }else{
            SceneEngine.firsttouch = true
            SceneEngine.paddleController.paddleNode = Paddle(PaddleImage: SceneEngine.paddleController.paddleImage)
            SceneEngine.paddleController = PaddleController()
            SceneEngine.paddleController.showPaddle(ToScene: view)
            SceneEngine.Ball = Projectile(BallTexture: Projectile.defaultBall, ToScene: view)
            view.addChild(SceneEngine.Ball!)

        }
    }
    
    
    public func showLives(ToScene view: GameScene){
        view.addChild(Label)
    }
    
    public func addLive(){
        if Label.CountLives < 6{
            Label.CountLives +=  1
            refreshLives()
        }
    }
    
    public func removeLive(){
        if Label.CountLives > 0{
            Label.CountLives -=  1
            refreshLives()
        }
    }
    
    public func resetLives(){
        Label.CountLives =  5
        refreshLives()
    }
    
    public func refreshLives(){
        
        Label.text = ""
        if Label.CountLives < 0 {
            print("lives is negative \(Label.CountLives)")
        }
        // it was !=0 wirft fehler beim gameover : countlives < 0 ?? 
        if Label.CountLives > 0{
            for _ in 0..<Label.CountLives{
                Label.text = Label.text! + "❤️"
            }
        }else{
            Label.text = ""
        }
    }
}
