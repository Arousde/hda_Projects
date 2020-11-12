//
//  GameViewController.swift
//  Breakout
//
//  Created by Arous Oussema on 13.08.19.
//  Copyright © 2019 Hochschule Darmstadt. All rights reserved.
//

import UIKit
import SpriteKit
import GameplayKit

class GameViewController: UIViewController {
    
    static public var paused = false
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        if let view = self.view as! SKView? {
            // Load the SKScene from 'GameScene.sks'
            if let scene = SKScene(fileNamed: "GameScene") {
                // Set the scale mode to scale to fit the window
                scene.scaleMode = .fill
                
                // Present the scene
                scene.physicsWorld.speed = 2
                view.isMultipleTouchEnabled = false
                view.presentScene(scene)
                
            }
            
            view.ignoresSiblingOrder = true
            
            view.showsFPS = true
            view.showsNodeCount = true

        }
    }
    
    
    

    

    override var shouldAutorotate: Bool {
        return true
    }

    override var supportedInterfaceOrientations: UIInterfaceOrientationMask {
      return .landscape
    }

    override var prefersStatusBarHidden: Bool {
        return true
    }
    
    
    
}
