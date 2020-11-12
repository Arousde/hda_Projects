//
//  BricksBuilder.swift
//  Breakout
//
//  Created by Arous Oussema on 17.08.19.
//  Copyright © 2019 Hochschule Darmstadt. All rights reserved.
//

import Foundation
import SpriteKit



class BricksBuilder {
    
    public static let Levels = ["apple","pacman","Mario","MarioEat","levelYoshi","MarioSpecial","yoshiGhost","Zelda","souhaila2","Goofy","levelFarben","ark1","ark2","ark3","ark4", "PixelArtLevel","levelIgelLove" , "levelNoten", "souhaila", "hunterxhunter1", "hunterxhunter2", "levelMikiMini", "freemap1"]
//    public static let Levels = ["levelFarben","pacman","Mario","ark1","ark2","ark3","ark4","levelFarben","apple","souhaila2","levelYoshi","levelIgelLove","PixelArtLevel","levelNoten","Goofy","souhaila", "levelMikiMini", "freemap1"]
    public static var levelIndex = 0
    
    var PowerupCntrl = PowerUpsController()
    
    var brick: Brick
    var mapindex = 0
    let numberOfBricks = 27
    let numberOfBlocks = 14
    var mapreader = mapReader()
    init() {
        brick = Brick(BrickImage: BrickImage.blue.rawValue)
    }
    
    public var countBricks: Array<Brick> = Array()
    
    func setcolorArray() -> Array<String> {
        var colors = Array<String>()
        colors.append(BrickImage.blue.rawValue)
        colors.append(BrickImage.green.rawValue)
        colors.append(BrickImage.pink.rawValue)
        colors.append(BrickImage.violet.rawValue)
        colors.append(BrickImage.yellow.rawValue)
        colors.append(BrickImage.sand.rawValue)
        colors.append(BrickImage.red.rawValue)
        colors.append(BrickImage.orange.rawValue)
        colors.append(BrickImage.lachs.rawValue)

        return colors
    }
    
    func AddPowerUp() {
       let random = Int.random(in: 0..<self.PowerupCntrl.setPowerups.count)
        PowerupCntrl.Powerup = PowerUp(fontName: "MarkerFelt-Wide", Power: "Power",  Powertext: PowerupCntrl.setPowerups[random])
        brick.Power = PowerupCntrl.Powerup
    }
    
    public func addaBrick(WithBrickImage image: String ) {
        if image == "none" {
            brick.brickimage = image
            brick.name = "brick"
            brick.brickwidth = SKSpriteNode(imageNamed: BrickImage.blue.rawValue).size.width
            brick.brickhigh = SKSpriteNode(imageNamed: BrickImage.blue.rawValue).size.height
            brick.zPosition = -10
            brick.setScale(0.5)
            
        }
        
        
        if image != "none" {
            if image != BrickImage.wall.rawValue{
                countBricks.append(brick)
                AddPowerUp()
            }
            brick.name = "brick"
            brick.brickimage = image
            brick.brickwidth = SKSpriteNode(imageNamed: image).size.width
            brick.brickhigh = SKSpriteNode(imageNamed: image).size.height
            brick.bricknode.zPosition = 3
            brick.setScale(0.5)
            var newBricksize = brick.size
            //resize to shape the body
            newBricksize.height = brick.frame.size.height / 2
            newBricksize.width =  brick.frame.size.width / 2
            //physical body
            
            brick.physicsBody = SKPhysicsBody(rectangleOf: newBricksize)
            brick.physicsBody?.isDynamic = false
            brick.physicsBody?.friction = 0
            brick.physicsBody?.restitution = 1
            brick.physicsBody?.usesPreciseCollisionDetection = true

            //bitmask
            brick.physicsBody?.categoryBitMask = PhysicsCategory.BrickCategory
            
        }
    }
    
    
    
    public func addablockofbricks( xoffset: inout CGFloat ,yoffset: CGFloat, nextblockX: inout CGFloat, colorIndex: Int , view: GameScene , screenorg: CGRect  ) {
        
        
        for _ in 0..<numberOfBricks {
            
            
            if mapreader.map[mapindex] == "b" {
                brick = Brick(BrickImage: BrickImage.blue.rawValue)
                addaBrick(WithBrickImage: BrickImage.blue.rawValue)
                brick.name = "blue"
                view.addChild(brick)
            }
            
            if mapreader.map[mapindex] == "g" {
                brick = Brick(BrickImage: BrickImage.green.rawValue)
                addaBrick(WithBrickImage: BrickImage.green.rawValue)
                brick.name = "green"
                view.addChild(brick)
            }
            if mapreader.map[mapindex] == "p" {
                brick = Brick(BrickImage: BrickImage.pink.rawValue)
                addaBrick(WithBrickImage: BrickImage.pink.rawValue)
                brick.name = "pink"
                view.addChild(brick)
                
            }
            if mapreader.map[mapindex] == "y" {
                brick = Brick(BrickImage: BrickImage.yellow.rawValue)
                addaBrick(WithBrickImage: BrickImage.yellow.rawValue)
                brick.name = "yellow"
                view.addChild(brick)
            }
            if mapreader.map[mapindex] == "v" {
                brick = Brick(BrickImage: BrickImage.violet.rawValue)
                addaBrick(WithBrickImage: BrickImage.violet.rawValue)
                brick.name = "violet"
                view.addChild(brick)
            }
            if mapreader.map[mapindex] == "w" {
                brick = Brick(BrickImage: BrickImage.wall.rawValue)
                addaBrick(WithBrickImage: BrickImage.wall.rawValue)
                brick.name = "wall"
                view.addChild(brick)
            }
        
            if mapreader.map[mapindex] == "s" {
                brick = Brick(BrickImage: BrickImage.sand.rawValue)
                addaBrick(WithBrickImage: BrickImage.sand.rawValue)
                brick.name = "sand"
                view.addChild(brick)
            }
            if mapreader.map[mapindex] == "l" {
                brick = Brick(BrickImage: BrickImage.lachs.rawValue)
                addaBrick(WithBrickImage: BrickImage.lachs.rawValue)
                brick.name = "lachs"
                view.addChild(brick)
            }
            if mapreader.map[mapindex] == "o" {
                brick = Brick(BrickImage: BrickImage.orange.rawValue)
                addaBrick(WithBrickImage: BrickImage.orange.rawValue)
                brick.name = "orange"
                view.addChild(brick)
            }
            if mapreader.map[mapindex] == "r" {
                brick = Brick(BrickImage: BrickImage.red.rawValue)
                addaBrick(WithBrickImage: BrickImage.red.rawValue)
                brick.name = "red"
                view.addChild(brick)
            }
            if mapreader.map[mapindex] == "G" {
                brick = Brick(BrickImage: BrickImage.grey.rawValue)
                addaBrick(WithBrickImage: BrickImage.grey.rawValue)
                brick.name = "Grey"
                view.addChild(brick)
            }
            if mapreader.map[mapindex] == "B" {
                brick = Brick(BrickImage: BrickImage.brown.rawValue)
                addaBrick(WithBrickImage: BrickImage.brown.rawValue)
                brick.name = "Grey"
                view.addChild(brick)
            }
            if mapreader.map[mapindex] == "a" {
                brick = Brick(BrickImage: BrickImage.white.rawValue)
                addaBrick(WithBrickImage: BrickImage.white.rawValue)
                brick.name = "Grey"
                view.addChild(brick)
            }
            if mapreader.map[mapindex] == "+" {
                brick = Brick(BrickImage: BrickImage.blue.rawValue)
                addaBrick(WithBrickImage: BrickImage.none.rawValue)
                
            }
            
            let xPos = xoffset + nextblockX
            let yPos = screenorg.maxY - ((brick.brickhigh  ) + (brick.brickhigh * yoffset ))
            brick.brickxPos = xPos
            brick.brickyPos = yPos
            brick.position = CGPoint(x: xPos, y: yPos)
            xoffset =  brick.position.x
            nextblockX = brick.brickwidth * 0.33
            
            mapindex = mapindex + 1
        }
    }
    
    public func addallBlocks(ToScene view: GameScene  ){
        //the actual level
        mapreader = mapReader(Level: BricksBuilder.Levels[BricksBuilder.levelIndex])
        countBricks.removeAll()
        
        let screenorg = CGRect(x:  view.frame.origin.x, y: view.frame.origin.y, width: view.frame.size.width, height: view.frame.size.height)
        var nextblockX = CGFloat(0.0)
        var xOffset = screenorg.minX + (SKSpriteNode(imageNamed: BrickImage.blue.rawValue).size.width   )
        var yOffset = CGFloat(0.0)
        var colorIndex = 0
        
        for _ in 0..<numberOfBlocks {
            self.addablockofbricks(xoffset: &xOffset, yoffset: yOffset, nextblockX: &nextblockX, colorIndex: colorIndex, view: view, screenorg: screenorg ) ;
            
            nextblockX = CGFloat(0.0)
            xOffset = screenorg.minX + (SKSpriteNode(imageNamed: BrickImage.blue.rawValue).size.width   )
            yOffset = yOffset + 0.33
            if colorIndex < 5 {
                colorIndex = colorIndex + 1
            }else{
                colorIndex = 2
            }
            
        }
        mapindex = 0
        
    }
    
    
    
    
    public static func cleanupForNextLevel(view: GameScene) {
        view.SceneEngine.inGame = false
        // add next label
        //cancel all jobs 
        PowerUpsController.CancelBallSpeedJob?.cancel()
        PowerUpsController.CancelBallPOwerJob?.cancel()
        // remove all Bricks ball paddle and PowerUps
        for b in view.children {
            if  let brick = b as? Brick {
                brick.removeFromParent()
            }
            if  let ball = b as? Projectile {
                ball.removeFromParent()
            }
            if  let paddle = b as? Paddle {
                paddle.removeFromParent()
            }
            if  let power = b as? PowerUp {
                power.removeFromParent()
            }
            if  let backdoor = b as? Backdoor {
                backdoor.removeFromParent()
            }
            if  let laser = b as? Laser {
                laser.removeFromParent()
            }
        }
        // add next label
        view.SceneEngine.gameController.gameConfig.background.zPosition = 8
        view.SceneEngine.gameController.addNext()
        view.addChild(view.SceneEngine.gameController.gameState.next)
        view.addChild(view.SceneEngine.gameController.gameState.Labelnext)
        
     
        //  prepare Builder for next level 
        if BricksBuilder.levelIndex < BricksBuilder.Levels.count - 1 {
            BricksBuilder.levelIndex = BricksBuilder.levelIndex + 1
            
        } else {
            BricksBuilder.levelIndex = 0
            
        }
        
    }
    
}
