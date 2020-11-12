//
//  GameScene.swift
//  Breakout
//
//  Created by Arous Oussema on 13.08.19.
//  Copyright © 2019 Hochschule Darmstadt. All rights reserved.
//

import SpriteKit
import GameplayKit
import AVFoundation

class GameScene: SKScene {
    let SceneEngine = ScEngine()
    let gameViewController = UIViewController()
    var LazerIndex = 6
    var MissileIndex = 11
   static  public var ScharedScene = GameScene()

    override func didMove(to view: SKView) {
      
        GameScene.ScharedScene = self
        
        SceneEngine.firsttouch = true
        //Audio player init
        
        SceneEngine.gameController.audioplayerInit()
        
        
        SceneEngine.gameController.showPlayView(WithImage: "background" , ToScene: self, position: 5)
        SceneEngine.gameController.gameConfig.audioPlayer.play()
        
        
        //  just for the moment
        //this line will init highscore to 0
        // HiScoreReader.initHighScore()
        // read the actual highscore
        HiScoreReader.readHiScore()
        
    }
    
    
    
    
    func touchDown(atPoint pos : CGPoint) {
        //        let nodes = self.nodes(at: pos)
        //        let play = SceneEngine.gameController.gameState.play
        //        print("touch pos : \(pos) Play pos : \(play.position)")
        //        if nodes.contains(play){
        //            SceneEngine.onPlayTouched(ToScene: self)
        //        }
        
        
    }
    
    func touchMoved(toPoint pos : CGPoint) {
        
    }
    
    func touchUp(atPoint pos : CGPoint) {
        
    }
    
    
    
    
    
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        let touch = touches.first
        let touchLocation = touch!.location(in: self)

     //   if  let b = physicsWorld.body(at: touchLocation){
      //      let body = b
            if let paddle = self.childNode(withName: "paddle")  as? Paddle{
                if touchLocation.y < -200 {
                    paddle.position.x = touchLocation.x
                    SceneEngine.paddleTouch()
                    // for sticky Ball
                    for node in self.children {
                        if let ball = node as? Projectile {
                            self.physicsWorld.remove(PowerUpsController.joint)
                            ball.physicsBody?.isDynamic = true
                        }}
                    
                }
               
        }
    }
    
    override func touchesMoved(_ touches: Set<UITouch>, with event: UIEvent?) {
        let touch = touches.first
        
        if !self.isPaused{
            SceneEngine.paddleController.paddleMove(touch: touch!, ToScene: self, from: SceneEngine)
        }
        
        
        
    }
    public func makePause(){
        SceneEngine.paused = true
        self.isPaused = true
        SceneEngine.gameController.gameState.pauseForViewIScreated = true
    }
    public func setPlayFlagsFalse(){
        SceneEngine.paused = false
        self.isPaused = false
        SceneEngine.gameController.gameState.pauseForViewIScreated = false
    }
    public func backHome(){
        SceneEngine.inGame = false
        setPlayFlagsFalse()
        BricksBuilder.levelIndex = 0
        // save new HighScore
        if SceneEngine.scoreController.score > Int(HiScoreReader.HighInt) {
            let newHighScore = SceneEngine.scoreController.score
            HiScoreReader.WriteNewHiScore(Name: "Arous", Hiscore: String(newHighScore))
            HiScoreReader.readHiScore()
        }
        self.removeAllChildren()
        
        didMove(to: self.view!)
    }
    private func alertLeaveGame(){
        
        
        let alert = UIAlertController(title: "Back to Home", message: "do you really want to Quit the Game?", preferredStyle: .alert)
        alert.addAction(UIAlertAction(title: "Resume Game", style: .cancel, handler: {action in self.makePause()}))
        alert.addAction(UIAlertAction(title: "Quit Game", style: .destructive, handler: {action in self.backHome()}))
        self.view?.window?.rootViewController?.present(alert, animated: true)

    }
    private func alertReplayLevel(touchLocation: CGPoint){
        
        
        let alert = UIAlertController(title: "Replay Level", message: "do you really want to Replay the Game?", preferredStyle: .alert)
        alert.addAction(UIAlertAction(title: "Resume Game", style: .cancel, handler: {action in self.makePause()}))
        alert.addAction(UIAlertAction(title: "Replay Game", style: .destructive, handler: {action in self.SceneEngine.gameOver(at: touchLocation, ToScene: self)}))
        self.view?.window?.rootViewController?.present(alert, animated: true)
        
    }
    override func touchesEnded(_ touches: Set<UITouch>, with event: UIEvent?) {
        //reset Flag needed for Paddle
        SceneEngine.isFingerOnPaddle = false
        
        let touch = touches.first
        let touchLocation = touch!.location(in: self)
        
        if  let body = physicsWorld.body(at: touchLocation){
            
            switch body.node!.atPoint(touchLocation).name{
            case SceneEngine.gameController.gameState.play.name:
                SceneEngine.inGame = true
                SceneEngine.onPlayTouched(ToScene: self)
                break

            case SceneEngine.gameController.gameState.back.name:

                if !SceneEngine.gameController.gameState.pauseForViewIScreated && SceneEngine.inGame{
                    SceneEngine.paused = true
                    self.isPaused = true
                    SceneEngine.gameController.showPausedView(ToScene: self)
                }
               // PowerUpsController.paddleScaleQue?.suspend()
                alertLeaveGame()
                break
            case SceneEngine.gameController.gameState.next.name:
                SceneEngine.paused = false
                self.isPaused = false
                SceneEngine.inGame = true
                SceneEngine.makeNextlevel(ToScene: self)
                break
            case SceneEngine.gameController.gameState.pause.name:
                if self.isPaused == true{
                    self.isPaused = false
                    SceneEngine.paused = false
                }else{
                    SceneEngine.gameController.showPausedView(ToScene: self)
                    self.isPaused = true
                    SceneEngine.paused = true
                }
                break
            case SceneEngine.gameController.gameState.pauseForView.name:
                if self.isPaused == true{
                    self.isPaused = false
                    SceneEngine.paused = false
//                    PowerUpsController.paddleScaleQue?.resume()
                }
                SceneEngine.gameController.deletePausedView(ToScene: self)
                break
            case SceneEngine.gameController.gameState.littleReplay.name:
                
                if !SceneEngine.gameController.gameState.pauseForViewIScreated && SceneEngine.inGame{
                    SceneEngine.paused = true
                    self.isPaused = true
                    SceneEngine.gameController.showPausedView(ToScene: self)
                }
                
                alertReplayLevel(touchLocation: touchLocation)
                
                break
            case .none:
                break
            case .some(_):
                break
                
            }
            if let livesController = SceneEngine.livesController{
                if livesController.Label.CountLives <= 0{
                    if body.node!.atPoint(touchLocation).name == SceneEngine.gameController.gameState.restartNode.name {
                        
                        SceneEngine.gameOver(at: touchLocation, ToScene: self)
                        return
                    }
                }
            }
          
        
        }
    }
    
    
    
    
    
    override func touchesCancelled(_ touches: Set<UITouch>, with event: UIEvent?) {
        for t in touches { self.touchUp(atPoint: t.location(in: self)) }
    }
    
    
    override func update(_ currentTime: TimeInterval) {
        
        
        
        
        if SceneEngine.paused{
            self.isPaused = true
            if !SceneEngine.gameController.gameState.pauseForViewIScreated{
                        SceneEngine.gameController.showPausedView(ToScene: self)
            }
            }
        
        
       if !SceneEngine.firsttouch{
        
        for Ball in self.children{
            if  let b = Ball as? Projectile {

                if b.physicsBody!.velocity.dx < 0 {
                    // velocity.dx < 150 is too bad
                    b.physicsBody!.velocity.dx = Projectile.BallvelocityDxMin
                }
                else {
                    b.physicsBody!.velocity.dx = Projectile.BallvelocityDxMax
                }
                if b.physicsBody!.velocity.dy < 0 {
                    b.physicsBody!.velocity.dy = Projectile.BallvelocityDyMin
                }
                else {
                    b.physicsBody!.velocity.dy = Projectile.BallvelocityDyMax
                }
                
            }
        }
        }
        if LazerIndex > 5 {
            if SceneEngine.paddleController.redPaddle == SceneEngine.paddleController.paddleNode.texture{
                
                SceneEngine.bricksBuilder.PowerupCntrl.showLaserAnimation(ToScene: self)
            }
            LazerIndex = 0
        }
        
        LazerIndex += 1
            
        if MissileIndex > 10 {
            if SceneEngine.paddleController.MissilePaddle == SceneEngine.paddleController.paddleNode.texture{
                
                SceneEngine.bricksBuilder.PowerupCntrl.FireMissile(ToScene: self)
            }
            MissileIndex = 0
        }
        
        MissileIndex += 1

        
    }
    
    
    
}
