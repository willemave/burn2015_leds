import Cocoa

//class View: NSView
//{
//  override func drawRect(dirtyRect: NSRect)
//  {
//    var bPath:NSBezierPath = NSBezierPath(rect: dirtyRect)
//    let fillColor = NSColor(red: 0.5, green: 0.0, blue: 0.5, alpha: 1.0)
//    fillColor.set()
//    bPath.fill()
//    
//    let borderColor = NSColor(red: 1.0, green: 0.0, blue: 0.0, alpha: 1.0)
//    borderColor.set()
//    bPath.lineWidth = 12.0
//    bPath.stroke()
//    
//    let circleFillColor = NSColor(red: 0.0, green: 1.0, blue: 0.0, alpha: 1.0)
//    var circleRect = NSMakeRect(dirtyRect.size.width/4, dirtyRect.size.height/4, dirtyRect.size.width/2, dirtyRect.size.height/2)
//    var cPath: NSBezierPath = NSBezierPath(ovalInRect: circleRect)
//    circleFillColor.set()
//    cPath.fill()
//  }
//}

class BaseViewControler: NSViewController {
  
  override func loadView() {
    let view = NSView(frame: NSMakeRect(0,0,100,100))
    view.wantsLayer = true
    view.layer?.borderWidth = 2
    view.layer?.borderColor = NSColor.redColor().CGColor
    self.view = view
  }

  
  override var representedObject: AnyObject? {
    didSet {
      // Update the view, if already loaded.
    }
  }
}

