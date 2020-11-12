//
//  MapReader.swift
//  Breakout
//
//  Created by Arous Oussema on 15.08.19.
//  Copyright © 2019 Hochschule Darmstadt. All rights reserved.
//

import Foundation

class mapReader {
    init() {}
    public  var map = [String()]
    init(Level: String) {
        map = readLevel(L: Level)
    }
    public func readLevel(L: String) -> [String] {
        
        var line = [String()]
        var newline = [String()]
        
        if let url = Bundle.main.url(forResource: L, withExtension: "txt"){
            if let text = try? String(contentsOf: url) {
                for char in text {
                    line.append(String(char))
                }
                
            }
            
        }
        for char in line {
            let test = String(char.filter { !" \n\t\r".contains($0)})
            if test != "" {
                newline.append(test)
            }
        }
        newline.remove(at: 0)
        return newline
    }
    
    
}
