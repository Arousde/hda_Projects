//
//  Brick.swift
//  Breakout
//
//  Created by Arous Oussema on 15.08.19.
//  Copyright © 2019 Hochschule Darmstadt. All rights reserved.
//

import Foundation
import SpriteKit

enum BrickImage : String {
    case blue = "blue"
    case green = "green"
    case pink = "pink"
    case violet = "violette"
    case yellow = "yellow"
    case sand = "sand"
    case red = "red"
    case orange = "orange"
    case lachs = "lachs"
    case white = "white"
    case brown = "brown"
    case grey = "grey"
    case wall = "black"
    case none = "none"
}

class Brick: SKSpriteNode {
    
    var bricknode: SKSpriteNode
    var brickwidth: CGFloat
    var brickhigh: CGFloat
    var Power: PowerUp
    var brickimage: String {
        didSet {
            if self.brickimage == BrickImage.wall.rawValue{
                self.hitpoint = 0
                self.hits = 0
            }
            else if  self.brickimage == BrickImage.blue.rawValue{
                self.hitpoint = 3
                self.hits = 2

                
            }   else if  self.brickimage == BrickImage.green.rawValue{
                self.hitpoint = 2
                self.hits = 1

                
            }   else {
                self.hitpoint = 1
                self.hits = 0

            }
        }
    }
    
    var brickxPos: CGFloat
    var brickyPos: CGFloat
    public  var hitpoint: Int
    public  var hits: Int
    
    init(BrickImage: String) {
        let texture = SKTexture(imageNamed: BrickImage)
         bricknode = SKSpriteNode()
         brickwidth = CGFloat()
         brickhigh = CGFloat()
         brickxPos = CGFloat()
         brickyPos = CGFloat()
         hitpoint = Int()
         hits = Int()
         brickimage = BrickImage
         Power = PowerUp()
        super.init(texture: texture, color: .clear , size: texture.size())

    }
    
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    
}
