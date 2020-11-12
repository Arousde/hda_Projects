//
//  Paddle.swift
//  Breakout
//
//  Created by Sonya Hedider on 14.08.19.
//  Copyright © 2019 Hochschule Darmstadt. All rights reserved.
//

import Foundation
import SpriteKit


class Paddle : SKSpriteNode {
    var paddleXmin: CGFloat
    var paddleXmax: CGFloat
    var paddleYmin: CGFloat
    var paddleYmax: CGFloat
    var paddleOffsetY: CGFloat
    var paddleOffsetMin: CGFloat
    var paddleOffsetMax: CGFloat
    var Paddleheight: CGFloat
    var Paddlewidth: CGFloat
    var paddleNode: SKSpriteNode
    
    init(PaddleImage: String) {
        let texture = SKTexture(imageNamed: PaddleImage)
        
        paddleXmin = CGFloat()
        paddleXmax = CGFloat()
        paddleYmin = CGFloat()
        paddleYmax = CGFloat()
        paddleOffsetY = CGFloat()
        paddleOffsetMin = CGFloat()
        paddleOffsetMax = CGFloat()
        Paddleheight = CGFloat()
        Paddlewidth = CGFloat()
        paddleNode = SKSpriteNode()
        
        super.init(texture: texture, color: .clear , size: texture.size())
        
    }
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    


}
