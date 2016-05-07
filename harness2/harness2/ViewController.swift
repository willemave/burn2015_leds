//
//  ViewController.swift
//  harness2
//
//  Created by Willem Ave on 4/7/16.
//  Copyright © 2016 Willem Ave. All rights reserved.
//

import Cocoa

class ViewController: NSViewController {
  
  class SquareWithCircleView: NSView{
    override func drawRect(dirtyRect: NSRect)
    {
      var bPath = NSBezierPath(rect: dirtyRect)
      let fillColor = NSColor(red: 0.5, green: 0.0, blue: 0.5, alpha: 1.0)
      fillColor.set()
      bPath.fill()
      
      let borderColor = NSColor(red: 1.0, green: 0.0, blue: 0.0, alpha: 1.0)
      borderColor.set()
      bPath.lineWidth = 12.0
      bPath.stroke()
      
      let circleFillColor = NSColor(red: 0.0, green: 1.0, blue: 0.0, alpha: 1.0)
      var circleRect = NSMakeRect(dirtyRect.size.width/4, dirtyRect.size.height/4, dirtyRect.size.width/2, dirtyRect.size.height/2)
      var cPath = NSBezierPath(ovalInRect: circleRect)
      circleFillColor.set()
      cPath.fill()
    }
  }
  
  override func viewDidLoad() {
    super.viewDidLoad()
    let circleView = SquareWithCircleView(frame: CGRect(x: 0, y: 0, width: 600, height: 500))
    
    
    self.view.addSubview(circleView)
    
    // Do any additional setup after loading the view.
  }

  override var representedObject: AnyObject? {
    didSet {
    // Update the view, if already loaded.
    }
  }


}

