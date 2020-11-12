//
//  Score.swift
//  Breakout
//
//  Created by Arous Oussema on 15.08.19.
//  Copyright © 2019 Hochschule Darmstadt. All rights reserved.
//

import Foundation
import SpriteKit
import AVFoundation

class Score: SKLabelNode {
    
    //var scoreLabel = SKLabelNode()
    
    public var score = 0
    var positionX = CGFloat()
    var positionY = CGFloat()
    var scoreMinX = CGFloat()
    var firstTimeFlag = 0
    var firstTimeFlagPoints = 0
    var points = 0
    
    override init() {
        
        super.init()
    }
    
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}
