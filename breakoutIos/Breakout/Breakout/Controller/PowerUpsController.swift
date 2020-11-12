//
//  PowerUpsController.swift
//  Breakout
//
//  Created by Arous Oussema on 23.08.19.
//  Copyright © 2019 Hochschule Darmstadt. All rights reserved.
//

import Foundation
import SpriteKit
class PowerUpsController {
    public static var StickyBall: Projectile?

    public static var BAllIndexName = 0
    let setPowerups = ["C","E","L","💝","S","D","B","P","M"]
    // init Jobs with Optional
    public static var CancelBallPOwerJob: DispatchWorkItem?
    public static var CancelBallSpeedJob: DispatchWorkItem?
    public static var CancelpaddleScaleJob: DispatchWorkItem?
    public static var CancelMagneticPaddle: DispatchWorkItem?
    public static var CancellaserPaddle: DispatchWorkItem?
    public static var CancelMissilePaddle: DispatchWorkItem?

   public static var joint = SKPhysicsJointFixed()

    
    public static func CancelAllJobsTimers() {
         CancelBallPOwerJob?.cancel()
         CancelBallSpeedJob?.cancel()
         CancelpaddleScaleJob?.cancel()
         CancelMagneticPaddle?.cancel()
         CancellaserPaddle?.cancel()
         CancelMissilePaddle?.cancel()

    }
    
  //  public static var paddleScaleDispatchQueue: DispatchQueue?
  //  public static var paddleScaleQue: DispatchQueue?
    
    init() {}
var hasBallPowerUp = false
var HasPaddlePowerUp = false
var canDropPowerUp = true
let plus = SKLabelNode()
var Powerup = PowerUp()
static var candrop = true
public var redPaddle = false
var laser: Laser?
var missile: Missile?

var backdoor: Backdoor?
var isreadyToFire = true
var ActualBallVelocity: CGFloat = 0.0
    
    
    
    public func dropPowerUp(brick: Brick, view: GameScene){
        // if brick has a PowerUp.  Wall dont have
        if brick.Power.power == "Power" {
            if canDropPowerUp {
                let P = brick.Power
                P.position = brick.position
                view.addChild(P)
                P.physicsBody!.applyImpulse(CGVector(dx: 0.0, dy: -2.0))
                canDropPowerUp = false
                // can drop next time only after 10 sec
                DispatchQueue.main.asyncAfter(deadline: .now() + 5) {
                    self.canDropPowerUp = true
                }
                
            }
            
        }
    }
    var spd = true
    public func eat(ToScene view: GameScene,Power:PowerUp){
        // Speed
        if Power.powertext == "S" {
            addSpeedTOBall(view: view)

        }
        else if Power.powertext == "C" {
            magneticPaddlePowerUp(ToScene: view)
        }
        else if Power.powertext == "E" {
            paddleScalePowerUp(ToScene: view)

        }
            //  Power
        else if Power.powertext == "L" {
            laserPaddePowerUp(ToScene: view)
        }
        else if Power.powertext == "💝" {
            extraLivePowerUp(ToScene: view)
        }else if Power.powertext == "P" {
            addPowerTOBall(view: view)
        }
        else if Power.powertext == "D" {
            addTowBalls(view: view)
        }
        else if Power.powertext == "B" {
            makeBackDoor(ToScene: view)
        }
        else if Power.powertext == "M" {
          MissilePaddePowerUp(ToScene: view)
        }

//        addPowerTOBall(view: view)
//        extraLivePowerUp(ToScene: view)
//        paddleScalePowerUp(ToScene: view)
//        magneticPaddlePowerUp(ToScene: view)
//        laserPaddePowerUp(ToScene: view)
        
//        plus.position = view.SceneEngine.paddleController.paddleNode.position
//        plus.position.y = view.SceneEngine.paddleController.paddleNode.position.y + view.SceneEngine.paddleController.paddleNode.paddleOffsetY + 50
//        plus.text = "🎁"
//        plus.fontSize = 30
//        plus.zPosition = 5
//        plus.fontColor = #colorLiteral(red: 0.8078431487, green: 0.02745098062, blue: 0.3333333433, alpha: 1)
//        // points.fontName = "GillSans-UltraBold"
//        plus.fontName = "MarkerFelt-Wide"
//        view.addChild(plus)
//
//        let action = SKAction.moveTo(y: plus.position.y + 50, duration: 0.5)
//        let sequence = SKAction.sequence([action, .removeFromParent()])
//        plus.run(sequence)
        
    }
    
    public func extraLivePowerUp(ToScene view: GameScene){
        view.SceneEngine.livesController!.addLive()
    }
    
    public func paddleScalePowerUp(ToScene view: GameScene){
        
         var newsize = view.SceneEngine.paddleController.paddleNode.size
        newsize.width += 30
        view.SceneEngine.paddleController.paddleNode.scale(to:newsize)

       PowerUpsController.CancelpaddleScaleJob = DispatchWorkItem {
        if view.SceneEngine.paddleController.paddleNode.size.width > PaddleController.OriginalPaddleSize.width {
            var newsize = view.SceneEngine.paddleController.paddleNode.size
            newsize.width -= 30
            view.SceneEngine.paddleController.paddleNode.scale(to:newsize)
        }
   
        }
        
        
        //Set The Timer and execute the Job
        if let job = PowerUpsController.CancelpaddleScaleJob {
            DispatchQueue.global().asyncAfter(deadline: .now() + 10, execute: job)
            
        }
//        PowerUpsController.paddleScaleQue = DispatchQueue(label: "com.ArousHedider.Breakout.paddleScale")
//
//        PowerUpsController.paddleScaleQue?.asyncAfter(deadline: .now() + .seconds(8) , execute: paddleScaleJob)
//
        
    }
    
    public func magneticPaddlePowerUp(ToScene view: GameScene){
        PowerUpsController.CancelMagneticPaddle?.cancel()
        view.SceneEngine.paddleController.paddleNode.texture = view.SceneEngine.paddleController.violetMagnetPaddle
        for node in view.children {
            if let ball = node as? Projectile {
                ball.changeImage(BallTexture: Projectile.violetBall)

            }
        }
        //Enter Here Ball Physics changement FOR STICKING INTO THE PADDLE
        
        
       PowerUpsController.CancelMagneticPaddle = DispatchWorkItem {
        
        if view.SceneEngine.paddleController.paddleNode.texture == view.SceneEngine.paddleController.violetMagnetPaddle {
            view.SceneEngine.paddleController.paddleNode.texture = view.SceneEngine.paddleController.greyPaddle
        }
        }
        
        //Set The Timer and execute the Job
        if let job = PowerUpsController.CancelMagneticPaddle {
            DispatchQueue.global().asyncAfter(deadline: .now() + 10, execute: job)

            
            
        }
        
        }
    
    
    public func laserPaddePowerUp(ToScene view: GameScene){
        PowerUpsController.CancellaserPaddle?.cancel()
        view.SceneEngine.paddleController.paddleNode.texture = view.SceneEngine.paddleController.redPaddle
        self.redPaddle = true
        
 PowerUpsController.CancellaserPaddle = DispatchWorkItem{
    if view.SceneEngine.paddleController.paddleNode.texture == view.SceneEngine.paddleController.redPaddle{
        view.SceneEngine.paddleController.paddleNode.texture = view.SceneEngine.paddleController.greyPaddle
        self.redPaddle = false
    }

    
        }
        
        //Set The Timer and execute the Job
    if let job = PowerUpsController.CancellaserPaddle {
            DispatchQueue.global().asyncAfter(deadline: .now() + 5, execute: job)
        
        }
        
    }
    

    
    public func bombPaddlePowerUp(ToScene view: GameScene){
        
    }
    
    
    public func addPowerTOBall(view: GameScene){
        initAllBallPowerUps(view: view)
        //change Ball Collision to go through bricks
        for nodes in view.children {
            if let ball = nodes as? Projectile{
                
                
                ball.changeImage(BallTexture: Projectile.redBall)
                ball.physicsBody?.collisionBitMask =  PhysicsCategory.BorderCategory | PhysicsCategory.PaddleCategory | PhysicsCategory.BallCategory
            }}
        // Set the Job to Do
        PowerUpsController.CancelBallPOwerJob = DispatchWorkItem {
            //  reset collison with bricks after 10 sec
            for nodes in view.children {
                if let ball = nodes as? Projectile{
                    do {
                        try ball.resetBallCollisionInTimer()
                        try ball.changeImageInTimer(BallTexture: Projectile.defaultBall)
                    }
                    catch{
                        print("YOUR APP HAS SURVIVED :: eroor : ")
                    }
                   
                    
                    
                    
                }
            }
            
        }
        //Set The Timer and execute the Job
        if let job = PowerUpsController.CancelBallPOwerJob {
            DispatchQueue.global().asyncAfter(deadline: .now() + 10, execute: job)
            
        }
    }
    
    
    
    func Speed(){
        Projectile.BallvelocityDxMax = 151.1
        Projectile.BallvelocityDxMin = -151.1
        
        Projectile.BallvelocityDyMax = 151.1
        Projectile.BallvelocityDyMin = -151.1
    }
    
    func backToACTUALSpeed(){
        Projectile.BallvelocityDxMax = ActualBallVelocity
        Projectile.BallvelocityDxMin = -ActualBallVelocity
        
        Projectile.BallvelocityDyMax = ActualBallVelocity
        Projectile.BallvelocityDyMin = -ActualBallVelocity
    }
    
    public func addSpeedTOBall(view: GameScene){
        
        initAllBallPowerUps(view: view)
        Speed()
        for nodes in view.children {
            if let ball = nodes as? Projectile{
                ball.changeImage(BallTexture: Projectile.blueBall)
                
            }}
        // Set the Job to Do
        PowerUpsController.CancelBallSpeedJob = DispatchWorkItem {
            
           self.backToACTUALSpeed()
            for nodes in view.children {
                if let ball = nodes as? Projectile{
                    do {
                        try ball.changeImageInTimer(BallTexture: Projectile.defaultBall)
                    }
                    catch{
                        print("YOUR APP HAS SURVIVED :: eroor :")
                    }                }}
            
        }
        //Set The Timer and execute the Job
        if let job = PowerUpsController.CancelBallSpeedJob {
            DispatchQueue.global().asyncAfter(deadline: .now() + 10, execute: job)
            
        }
        
    }
    
    
    
    
    public func initAllBallPowerUps(view: GameScene){
        // Stop All cancelling Jobs for the ball
        PowerUpsController.CancelBallSpeedJob?.cancel()
        PowerUpsController.CancelBallPOwerJob?.cancel()
        
        // reset Projrctile Velocity
        if Projectile.BallvelocityDxMax > 200.0 {
            ActualBallVelocity = Projectile.BallvelocityDxMax
        }
        if ActualBallVelocity > 0.0 {
            backToACTUALSpeed()
        }
        
        // reset all balls
        for nodes in view.children {
            if let ball = nodes as? Projectile{
                //reset Ball image
                ball.changeImage(BallTexture: Projectile.defaultBall)
                // reset Ball Collision
                ball.physicsBody?.collisionBitMask = PhysicsCategory.BrickCategory | PhysicsCategory.BorderCategory | PhysicsCategory.PaddleCategory | PhysicsCategory.BallCategory
                
            }
        }
    }
    
    public func addTowBalls(view: GameScene){
      var ball: Projectile?
        for b in view.children{
            if b is Projectile {
                ball = b as? Projectile
                break
            }
        }
        
        if let Ball = ball{
            let ball2 = Projectile(BallTexture: Projectile.defaultBall, ToScene: view)
            ball2.name = "ball \(PowerUpsController.BAllIndexName)"
            ball2.position = Ball.position
            view.addChild(ball2)
            PowerUpsController.BAllIndexName += 1
            let ball3 = Projectile(BallTexture: Projectile.defaultBall, ToScene: view)
            ball2.name = "ball \(PowerUpsController.BAllIndexName)"

            ball3.position = Ball.position

            view.addChild(ball3)
            PowerUpsController.BAllIndexName += 1

            ball2.physicsBody?.velocity = CGVector(dx: 40, dy: 10)
            ball3.physicsBody?.velocity = CGVector(dx: -40, dy: 10)
        }
       
        
    }
    public func showLaserAnimation(ToScene view: GameScene){
        
        showLaser(ToScene: view)
        
    }
    
    public func showLaser(ToScene view: GameScene){
        laser = Laser(View: view)
    }
    
    public func FireMissile(ToScene view: GameScene){
        missile = Missile(View: view)
    }
    
    public func MissilePaddePowerUp(ToScene view: GameScene){
        PowerUpsController.CancelMissilePaddle?.cancel()
        view.SceneEngine.paddleController.paddleNode.texture = view.SceneEngine.paddleController.MissilePaddle
        
        PowerUpsController.CancelMissilePaddle = DispatchWorkItem {
            if view.SceneEngine.paddleController.paddleNode.texture == view.SceneEngine.paddleController.MissilePaddle {
                view.SceneEngine.paddleController.paddleNode.texture = view.SceneEngine.paddleController.greyPaddle
            }
        }
        
        //Set The Timer and execute the Job
        if let job = PowerUpsController.CancelMissilePaddle {
            DispatchQueue.global().asyncAfter(deadline: .now() + 5, execute: job)
            
        }
        
    }
    
    func makeBackDoor(ToScene view: GameScene) {
        for doors in view.children{
            if doors is Backdoor {
                return
            }}
      backdoor = Backdoor(View: view)
    }
    
    public func PowerGoNextLevel(view: GameScene){
        
        view.SceneEngine.inGame = false
        view.SceneEngine.gameController.gameState.pauseForViewIScreated = false
        BricksBuilder.cleanupForNextLevel(view: view)
    }
    
    
    
}
