//
//  GameStateController.swift
//  Breakout
//
//  Created by Sonya Hedider on 18.08.19.
//  Copyright © 2019 Hochschule Darmstadt. All rights reserved.
//

import Foundation
import SpriteKit
import AVFoundation


class GameController{
    var gameState = GameState()
    var gameConfig = GameConfig()
    
    
    public func showLittlereplay(ToScene view: GameScene){
        let screenorg = CGRect(x:  view.frame.origin.x, y: view.frame.origin.y, width: view.frame.size.width, height: view.frame.size.height)
        
        gameState.littleReplay = SKSpriteNode(imageNamed: "littleReplay")
        gameState.littleReplay.name = "littleReplay"
        gameState.littleReplay.position = CGPoint(x: screenorg.maxX - gameState.back.size.width - 60, y: screenorg.maxY - 40)
        gameState.littleReplay.setScale(0.3)
        
        gameState.littleReplay.physicsBody = SKPhysicsBody(rectangleOf: gameState.littleReplay.size)
        gameState.littleReplay.physicsBody?.isDynamic = false
        
        gameState.littleReplay.physicsBody?.categoryBitMask = PhysicsCategory.littleReplay
        
        gameState.littleReplay.physicsBody?.contactTestBitMask = 0
        gameState.littleReplay.physicsBody?.collisionBitMask = 0
        
        
        view.addChild(gameState.littleReplay)
    }
    
    public func showPause(ToScene view: GameScene){
        let screenorg = CGRect(x:  view.frame.origin.x, y: view.frame.origin.y, width: view.frame.size.width, height: view.frame.size.height)
        
        gameState.pause = SKSpriteNode(imageNamed: "pause")
        gameState.pause.name = "pause"
        gameState.pause.position = CGPoint(x: gameState.back.position.x, y: screenorg.maxY - gameState.back.position.y/3)
        gameState.pause.setScale(0.30)
        
                gameState.pause.physicsBody = SKPhysicsBody(rectangleOf: gameState.pause.size)
                gameState.pause.physicsBody?.isDynamic = false
                gameState.pause.physicsBody?.categoryBitMask = PhysicsCategory.PauseCategory
        
                gameState.pause.physicsBody?.contactTestBitMask = 0
        view.addChild(gameState.pause)
    }
    
//    public func paused(){
//        gameState.LabelPause.name = "pause"
//        gameState.LabelPause.text = "PAUSE"
//        gameState.LabelPause.fontColor = #colorLiteral(red: 0, green: 0, blue: 0, alpha: 1)
//        gameState.LabelPause.fontSize = 100
//        gameState.LabelPause.zPosition = 10
//        gameState.LabelPause.fontName = "AvenirNext-Bold"
//        gameState.LabelPause.horizontalAlignmentMode = .center
//        gameState.LabelPause.position = CGPoint(x: 0, y: 60)
//        //Label.categoryBitMask = PhysicsCategory.BottomCategory
//
//
//        gameState.play = SKSpriteNode(imageNamed: "pause")
//        gameState.play.name = "pause"
//        gameState.play.zPosition = 10
//        gameState.play.position = CGPoint(x: 0,y: -60)
//        gameState.play.setScale(0.4)
//
//        gameState.play.physicsBody = SKPhysicsBody(rectangleOf: gameState.play.frame.size)
//        gameState.play.physicsBody?.isDynamic = false
//    }
    
    public func showPlay(){
        gameState.LabelPlay.name = "Play"
        gameState.LabelPlay.text = "PLAY NEW GAME"
        gameState.LabelPlay.fontColor = #colorLiteral(red: 0, green: 0, blue: 0, alpha: 1)
        gameState.LabelPlay.fontSize = 100
        gameState.LabelPlay.zPosition = 10
        gameState.LabelPlay.fontName = "AvenirNext-Bold"
        gameState.LabelPlay.horizontalAlignmentMode = .center
        gameState.LabelPlay.position = CGPoint(x: 0, y: 60)
        //Label.categoryBitMask = PhysicsCategory.BottomCategory
        
        
        gameState.play = SKSpriteNode(imageNamed: "play")
        gameState.play.name = "play"
        gameState.play.zPosition = 10
        gameState.play.position = CGPoint(x: 0,y: -60)
        gameState.play.setScale(0.4)
        
        gameState.play.physicsBody = SKPhysicsBody(rectangleOf: gameState.play.size)
        gameState.play.physicsBody?.isDynamic = false
        
        
    }
    
    public func addNext(){
        gameState.Labelnext.name = "Next"
        gameState.Labelnext.text = "Next Level"
        gameState.Labelnext.fontColor = #colorLiteral(red: 0, green: 0, blue: 0, alpha: 1)
        gameState.Labelnext.fontSize = 100
        gameState.Labelnext.zPosition = 10
        gameState.Labelnext.fontName = "AvenirNext-Bold"
        gameState.Labelnext.horizontalAlignmentMode = .center
        gameState.Labelnext.position = CGPoint(x: 0, y: 60)
        //Label.categoryBitMask = PhysicsCategory.BottomCategory
        
        
        gameState.next = SKSpriteNode(imageNamed: "play")
        gameState.next.name = "next"
        gameState.next.zPosition = 10
        gameState.next.position = CGPoint(x: 0,y: -60)
        gameState.next.setScale(0.4)
        
        gameState.next.physicsBody = SKPhysicsBody(rectangleOf: gameState.next.size)
        gameState.next.physicsBody?.isDynamic = false
        
    }
    
    
    
    public func showGoBack(ToScene view: GameScene){
        
        
        
        let screenorg = CGRect(x:  view.frame.origin.x, y: view.frame.origin.y, width: view.frame.size.width, height: view.frame.size.height)
        
        gameState.back = SKSpriteNode(imageNamed: "back")
        gameState.back.name = "back"
        
//        gameState.backHeight = (gameState.back.frame.maxX - gameState.back.frame.minX)
//        gameState.backWidth = (gameState.back.frame.maxY - gameState.back.frame.minY)
//        gameState.back.position = CGPoint(x: screenorg.maxX - gameState.backWidth/2 + 50, y: screenorg.maxY - 40)
//        gameState.back.setScale(0.30)
        
                gameState.backHeight = (gameState.back.frame.maxX - gameState.back.frame.minX)
                gameState.backWidth = (gameState.back.frame.maxY - gameState.back.frame.minY)
                gameState.back.position = CGPoint(x: screenorg.maxX - gameState.backWidth/2 + 50 , y: screenorg.maxY - 40)
                gameState.back.setScale(0.30)
        gameState.back.zPosition = 15
        
                gameState.back.physicsBody = SKPhysicsBody(rectangleOf: gameState.back.size)
                gameState.back.physicsBody?.isDynamic = false
               gameState.back.physicsBody?.categoryBitMask = PhysicsCategory.BackCategory
                gameState.back.physicsBody?.collisionBitMask = 0
        view.addChild(gameState.back)
    }
    

    
    public func showGameOver(ToScene view: GameScene){
        if view.childNode(withName: "GameOver") != nil {
            return
        }
        if view.childNode(withName: "replay") != nil {
            return
        }
        
        gameState.LabelGameOver.name = "GameOver"
        gameState.LabelGameOver.text = "GAME OVER"
        gameState.LabelGameOver.fontColor = #colorLiteral(red: 0, green: 0, blue: 0, alpha: 1)
        gameState.LabelGameOver.fontSize = 100
        gameState.LabelGameOver.zPosition = 10
        gameState.LabelGameOver.fontName = "AvenirNext-Bold"
        gameState.LabelGameOver.horizontalAlignmentMode = .center
        gameState.LabelGameOver.position = CGPoint(x: 0, y: 60)
        //Label.categoryBitMask = PhysicsCategory.BottomCategory

        
        
        gameState.restartNode = SKSpriteNode(imageNamed: "replay")
        gameState.restartNode.name = "replay"
        gameState.restartNode.zPosition = 10
        gameState.restartNode.position = CGPoint(x: 0,y: -60)
        gameState.restartNode.setScale(0.5)
        
        gameState.restartNode.physicsBody = SKPhysicsBody(rectangleOf: gameState.restartNode.frame.size)
        gameState.restartNode.physicsBody?.isDynamic = false
        
        view.addChild(gameState.LabelGameOver)
        view.addChild(gameState.restartNode)
        
    }
     public func showPausedView(ToScene view: GameScene){
        gameState.pauseForViewIScreated = true
                gameState.LabelPause.name = "pause"
                gameState.LabelPause.text = "GAME PAUSED"
                gameState.LabelPause.fontColor = #colorLiteral(red: 0, green: 0, blue: 0, alpha: 1)
                gameState.LabelPause.fontSize = 100
                gameState.LabelPause.zPosition = 15
                gameState.LabelPause.fontName = "AvenirNext-Bold"
                gameState.LabelPause.horizontalAlignmentMode = .center
                gameState.LabelPause.position = CGPoint(x: 0, y: 60)
                //Label.categoryBitMask = PhysicsCategory.BottomCategory
        
        gameState.pause.removeFromParent()
        gameState.back.zPosition = 15
//        gameConfig.background.zPosition = 10
        
        gameState.pauseForView = SKSpriteNode(imageNamed: "play")
        gameState.pauseForView.name = "playViewNode"
        gameState.pauseForView.zPosition = 15
        gameState.pauseForView.position = CGPoint(x: 0,y: -60)
        gameState.pauseForView.setScale(0.4)
        
        gameState.pauseForView.physicsBody = SKPhysicsBody(rectangleOf: gameState.play.size)
        gameState.pauseForView.physicsBody?.isDynamic = false
        
        if view.childNode(withName: "pause") != nil {
            return
        }
        if view.childNode(withName: "playViewNode") != nil {
            return
        }
        view.addChild(gameState.pauseForView)
        view.addChild(gameState.LabelPause)
    }
    
    public func deletePausedView(ToScene view: GameScene){
        gameState.pauseForViewIScreated = false
        gameState.LabelPause.removeFromParent()
        gameState.pauseForView.removeFromParent()
        showPause(ToScene: view)
//        gameConfig.background.zPosition = -2
    }
    
    public func showPlayView(WithImage image: String , ToScene view: GameScene, position : CGFloat)  {
        showPlay()
        gameConfig.background = SKSpriteNode(imageNamed: image)
        gameConfig.background.name = image
        gameConfig.background.size = view.frame.size;
        gameConfig.background.zPosition = position
        view.addChild(gameConfig.background)
        view.addChild(gameState.play)
        view.addChild(gameState.LabelPlay)
    }
    
    public func deleteGameOverView(WithImage image: String , ToScene view: GameScene)  {
        showPlay()
        gameConfig.background = SKSpriteNode(imageNamed: image)
        gameConfig.background.name = image
        gameConfig.background.size = view.frame.size;
        gameConfig.background.zPosition = -2
        view.addChild(gameConfig.background)
    }
    
    public func makeBottom(ToScene view: GameScene, paddle: Paddle){
             let bottomRect = CGRect(x: view.frame.origin.x, y: view.frame.origin.y + 20, width: view.frame.size.width, height: 1)
        
        gameConfig.bottomNode.physicsBody = SKPhysicsBody(edgeLoopFrom: bottomRect)
        gameConfig.bottomNode.name = "bottom"
      
        gameConfig.bottomNode.physicsBody?.friction = 0
        gameConfig.bottomNode.physicsBody?.restitution = 1
        gameConfig.bottomNode.physicsBody?.isDynamic = false
        gameConfig.bottomNode.physicsBody?.categoryBitMask = PhysicsCategory.BottomCategory
        gameConfig.bottomNode.physicsBody?.contactTestBitMask = PhysicsCategory.BallCategory
        if view.childNode(withName: "bottom") != nil {
            return
        }
        view.addChild(gameConfig.bottomNode)
    }
    
    
    

    public func audioplayerInit(){
        do {
            try  gameConfig.audioPlayer = AVAudioPlayer(contentsOf: gameConfig.Introsound)
        } catch {
            print("Unexpected error: \(error).")
        }
        gameConfig.audioPlayer.prepareToPlay()
    }
    

    
}
