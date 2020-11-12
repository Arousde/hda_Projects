//
//  Score.swift
//  Breakout
//
//  Created by Arous Oussema on 15.08.19.
//  Copyright © 2019 Hochschule Darmstadt. All rights reserved.
//

import Foundation
import SpriteKit

class ScoreController {
    var scoreLabel: Score
    
    public var score = 0
    //will be counted to 100 for an extra Heart
    var scoreCounter = 0
    var positionX = CGFloat()
    var positionY = CGFloat()
    var scoreMinX = CGFloat()
    var firstTimeFlag = 0
    var firstTimeFlagPoints = 0
    
    var powerUp = SKLabelNode()
    
    
    init() {
        scoreLabel = Score()
    }
    public func schowScore(ToScene view: GameScene, from SceneEngine: ScEngine){
        score = 0
        let screenorg = CGRect(x:  view.frame.origin.x, y: view.frame.origin.y, width: view.frame.size.width, height: view.frame.size.height)
        
        scoreLabel.name = "Score"
        scoreLabel.fontColor = #colorLiteral(red: 0, green: 0, blue: 0, alpha: 1)
        scoreLabel.fontSize = 35
        scoreLabel.fontName = "Papyrus"
        //scoreLabel.fontName = "PartyLetPlain"
        //scoreLabel.text = "Score : \(self.score)"
        scoreLabel.text = "Score : \(self.score)      HighScore : \(HiScoreReader.HighScore)  "
        
        scoreLabel.horizontalAlignmentMode = .center
        
        if (firstTimeFlag == 0){
            scoreMinX = scoreLabel.frame.minX
            positionX =  SceneEngine.livesController!.Label.frame.maxX - (scoreLabel.frame.minX) + 120
            positionY = screenorg.maxY - (scoreLabel.frame.maxY) - 12
            firstTimeFlag = 1
        }
        
        
        scoreLabel.position = CGPoint(x: positionX,
                                      y: positionY)
        view.addChild(scoreLabel)
    }
    
    public func refreshScore(){
        scoreLabel.text = "Score : \(self.score)      HighScore : \(HiScoreReader.HighScore)  "
        // PointsLabel.text = "Points : \(BrickName) -> \(self.points) "
    }
    
    //    public func schowPoints(ToScene view: GameScene){
    //        let screenorg = CGRect(x:  view.frame.origin.x, y: view.frame.origin.y, width: view.frame.size.width, height: view.frame.size.height)
    //
    //        PointsLabel.name = "Points"
    //        PointsLabel.fontColor = #colorLiteral(red: 0, green: 0, blue: 0, alpha: 1)
    //        //     scoreLabel.fontSize = 32
    //        PointsLabel.fontName = "AvenirNext-Bold"
    //        PointsLabel.text = "Points : \(self.points)"
    //        PointsLabel.horizontalAlignmentMode = .center
    //
    //        if (firstTimeFlagPoints == 0){
    //            scoreMinX = PointsLabel.frame.minX
    //            positionX =  view.score.scoreLabel.frame.maxX - (PointsLabel.frame.minX) + 40
    //            positionY = screenorg.maxY - (PointsLabel.frame.maxY) - 5
    //            firstTimeFlagPoints = 1
    //        }
    //
    //
    //        PointsLabel.position = CGPoint(x: positionX,
    //                                      y: positionY)
    //        view.addChild(PointsLabel)
    //
    //    }
    
    
    
    func firePoints(brick: Brick, view: GameScene) {
        
        let color = [#colorLiteral(red: 0.2392156869, green: 0.6745098233, blue: 0.9686274529, alpha: 1),#colorLiteral(red: 0.1411764771, green: 0.3960784376, blue: 0.5647059083, alpha: 1),#colorLiteral(red: 0.05882352963, green: 0.180392161, blue: 0.2470588237, alpha: 1)]
        let points = SKLabelNode()
        points.position = brick.position
        points.text = String(brick.hitpoint)
        points.zPosition = 5
        points.fontColor = color[brick.hitpoint - 1]
        // points.fontName = "GillSans-UltraBold"
        points.fontName = "MarkerFelt-Wide"
        view.addChild(points)
        let moveto = CGVector(dx: 0, dy: 1100)
        let action = SKAction.move(by: moveto, duration: 5.0)
        let sequence = SKAction.sequence([action, .removeFromParent()])
        points.run(sequence)
    }
    
   
    func didwin(brick: Brick, view: GameScene, from SceneEngine: ScEngine){
        if let index = SceneEngine.bricksBuilder.countBricks.firstIndex(of: brick) {
            SceneEngine.bricksBuilder.countBricks.remove(at: index)
            
        }
        if SceneEngine.bricksBuilder.countBricks.isEmpty{
            // add sound
            
            
           brick.Power.removeFromParent()
            BricksBuilder.cleanupForNextLevel(view: view)
        }
    }
    
    public func hitBrick(brick: Brick, ToScene view: GameScene, from SceneEngine: ScEngine){
        if brick.name != "wall"{
            view.run(SceneEngine.gameController.gameConfig.bricksound)
            // representation of hitpoints with colored label
            firePoints(brick: brick, view: view)
            // new score
            score += brick.hitpoint
            
            scoreCounter += brick.hitpoint
            view.SceneEngine.addHearts()
            
            scoreLabel.points = brick.hitpoint
            refreshScore()
            
            // if the brick bricks
            if brick.hits == 0 {
                // add Power up logic
                view.SceneEngine.bricksBuilder.PowerupCntrl.dropPowerUp(brick: brick, view: view)
                
                brick.removeFromParent()
                // check if no bricks remain
                didwin(brick: brick, view: view, from: SceneEngine)
                
                
            }else{
                brick.hits = brick.hits - 1
            }
        }else{
        view.run(SceneEngine.gameController.gameConfig.wallsound)
        }
        
    }
    
    public func hitWallsBrick(brick: Brick, ToScene view: GameScene, from SceneEngine: ScEngine){
        if brick.name != "wall"{
            view.run(SceneEngine.gameController.gameConfig.bricksound)
            // representation of hitpoints with colored label
            firePoints(brick: brick, view: view)
            // new score
            score += brick.hitpoint
            
            scoreCounter += brick.hitpoint
            view.SceneEngine.addHearts()
            
            scoreLabel.points = brick.hitpoint
            
            
            
            
            refreshScore()
            // if the brick bricks
            if brick.hits == 0 {
                // add Power up logic
                view.SceneEngine.bricksBuilder.PowerupCntrl.dropPowerUp(brick: brick, view: view)
                
                brick.removeFromParent()
                // check if no bricks remain
                didwin(brick: brick, view: view, from: SceneEngine)
                
                
            }else{
                brick.hits = brick.hits - 1
            }
        }else{
            view.run(SceneEngine.gameController.gameConfig.wallsound)
            brick.removeFromParent()

        }
        
    }
    
    
}
