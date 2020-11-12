//
//  BallController.swift
//  Breakout
//
//  Created by Arous Oussema on 25.08.19.
//  Copyright © 2019 Hochschule Darmstadt. All rights reserved.
//

import Foundation

class BallController {
    
    public static var AllBallsInTheScene: [Projectile]?
    
    public func increaseBallSpeedWithTime() {
        
        DispatchQueue.global(qos: .background).async {
            
            while true {
                if Projectile.BallvelocityDxMax < 330.1 {
                    Projectile.BallvelocityDxMax = Projectile.BallvelocityDxMax + 5
                    Projectile.BallvelocityDyMax = Projectile.BallvelocityDxMax + 5
                    Projectile.BallvelocityDxMin = -Projectile.BallvelocityDxMax
                    Projectile.BallvelocityDyMin = -Projectile.BallvelocityDyMax
                }
                sleep(30)
            }
    }
    
}

}
