//: Playground - noun: a place where people can play

import UIKit
import SpriteKit
import XCPlayground

var str = "Hello, playground"

infix operator ** { associativity left precedence 200 }
func ** (base: Double, power: Double) -> Double {
  return exp(log(base) * power)
}

extension Double {
  var f:CGFloat { return CGFloat(self) }
}

struct SphereContext {
  var r = drand48()*180.0
  var p = drand48()*180.0
  var o = drand48()*180.0
  
  func toUIColor() -> UIColor {
    let X = r * cos(o) * cos(o)
    let Y = r * cos(o) * sin(o)
    let Z = r * sin(o)
    
    var var_X = X / 100.0        //X from 0 to  95.047      (Observer = 2°, Illuminant = D65)
    var var_Y = Y / 100.0        //Y from 0 to 100.000
    var var_Z = Z / 100.0        //Z from 0 to 108.883
    
    var var_R = var_X *  3.2406 + var_Y * -1.5372 + var_Z * -0.4986
    var var_G = var_X * -0.9689 + var_Y *  1.8758 + var_Z *  0.0415
    var var_B = var_X *  0.0557 + var_Y * -0.2040 + var_Z *  1.0570
    
    if var_R > 0.0031308 { var_R = 1.055 * ( var_R ** ( 1 / 2.4 ) ) - 0.055 }
    else {var_R = 12.92 * var_R    }
    if var_G > 0.0031308 { var_G = 1.055 * ( var_G ** ( 1 / 2.4 ) ) - 0.055 }
    else                     {var_G = 12.92 * var_G}
    if var_B > 0.0031308 {var_B = 1.055 * ( var_B ** ( 1 / 2.4 ) ) - 0.055}
    else                     {var_B = 12.92 * var_B}
    
    let R = var_R * 255
    let G = var_G * 255
    let B = var_B * 255
    
    return UIColor(red: R.f, green: G.f, blue: B.f, alpha: 0.2)
  }
}


//Create the SpriteKit View
let view:SKView = SKView(frame: CGRectMake(0, 0, 1024, 768))
XCPShowView("my SpriteKit view", view: view)
//Add it to the TimeLin

//Create the scene and add it to the view
let scene:SKScene = SKScene(size: CGSizeMake(1024, 768))
scene.scaleMode = SKSceneScaleMode.AspectFit


//Add something to it!
let redBox:SKSpriteNode = SKSpriteNode(color: SKColor.redColor(), size:CGSizeMake(300, 300))
redBox.position = CGPointMake(512, 384)
redBox.runAction(SKAction.customActionWithDuration(15, actionBlock: { (rb, dur) in
  let l = rb as! SKSpriteNode
  l.color = SphereContext().toUIColor()
}))
redBox.runAction(SKAction.repeatActionForever(SKAction.colorizeWithColor(SphereContext().toUIColor(), colorBlendFactor: 0.2, duration: 2)))
scene.addChild(redBox)
view.presentScene(scene)

//
//
//
//for time in 1...100 {
//  sleep(1);
//  let p = randRad()
//  let r = randRad() / 90.0
//  let o = randRad()
//  let x = r * cos(o) * cos(o)
//  let y = r * cos(o) * sin(o)
//    let z = r * sin(o)
//
//}
