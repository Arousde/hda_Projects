//
//  HiScoreReader.swift
//  Breakout
//
//  Created by Arous Oussema on 22.08.19.
//  Copyright © 2019 Hochschule Darmstadt. All rights reserved.
//

import Foundation

class HiScoreReader {
    
    static var NameAndHiscore = [String()]
    public static var Name = String()
    public static var HighScore = String()
    public static var HighInt = Int()
    static var firstTimeReadOnADevice = true
    init() {}
 

    static public func readHiScore(){
         do {
                let filename = HiScoreReader.getDocumentsDirectory().appendingPathComponent("HighScore.txt")
                let text = try String(contentsOf: filename)
                NameAndHiscore = text.components(separatedBy: .newlines)
                
                }
            catch{
                // Will Create a new file on first time usage   
                initHighScore()
        }
        
            HiScoreReader.Name = NameAndHiscore.removeFirst()
            HiScoreReader.HighScore = NameAndHiscore.first ?? "0"
            HiScoreReader.HighInt = Int(HiScoreReader.HighScore) ?? 0
        }
    
    
    
   static func getDocumentsDirectory() -> URL {
        let paths = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask)
        return paths[0]
    }
    
static  public func WriteNewHiScore(Name: String, Hiscore: String){
          var NameAndHighScore = "\(Name)\n\(Hiscore)"
    
    
            let filename = HiScoreReader.getDocumentsDirectory().appendingPathComponent("HighScore.txt")
            let data = Data(NameAndHighScore.utf8)
            do {
                try data.write(to: filename)
            }
            catch{
                print("cannot write on file with error :  \(error)")
                }
    
        }
    
    static  public func initHighScore(){
        if firstTimeReadOnADevice {
            var NameAndHighScore = "\("")\n\(0)"
            let filename = HiScoreReader.getDocumentsDirectory().appendingPathComponent("HighScore.txt")
            let data = Data(NameAndHighScore.utf8)
            do {
                try data.write(to: filename)
            }
            catch{
                print("cannot write on file with error :  \(error)")
            }
        }
    
        
    }
    
    }

