import Foundation
import SpriteKit
import AVFoundation

public struct PhysicsCategory {
    static let BallCategory   : UInt32 = 0x1 << 0
    static let BottomCategory : UInt32 = 0x1 << 1
    static let BrickCategory  : UInt32 = 0x1 << 2
    static let PaddleCategory : UInt32 = 0x1 << 3
    static let BorderCategory : UInt32 = 0x1 << 4
    static let PauseCategory  : UInt32 = 0x1 << 5
    static let LaserCategory  : UInt32 = 0x1 << 6
    static let PowerUp        : UInt32 = 0x1 << 7
    static let BackCategory   : UInt32 = 0x1 << 8
    static let Backdoor       : UInt32 = 0x1 << 9
    static let littleReplay   : UInt32 = 0x1 << 10
    static let MissileCategory  : UInt32 = 0x1 << 11

}
    
    
    
//    static let TopCategory    : UInt32 = 0x1 << 5
//    static let rightCategory  : UInt32 = 0x1 << 7
//}

class GameConfig{
    

    
    var bottomNode = SKNode()
    var background = SKSpriteNode()
    
    
    let Introsound = URL(fileURLWithPath: Bundle.main.path(forResource: "NES - Arkanoid - Sound Effects/Arkanoid", ofType: "wav")!)
    var audioPlayer = AVAudioPlayer()
    // initialize sounds
    let startsound = SKAction.playSoundFileNamed("NES - Arkanoid - Sound Effects/Arkanoidstart", waitForCompletion: false)
    let wallsound = SKAction.playSoundFileNamed("NES - Arkanoid - Sound Effects/wallball", waitForCompletion: false)
    let bricksound = SKAction.playSoundFileNamed("NES - Arkanoid - Sound Effects/brickball", waitForCompletion: false)
    let losesound = SKAction.playSoundFileNamed("NES - Arkanoid - Sound Effects/Arkanoid SFX (10)", waitForCompletion: false)
    

    
    
}
