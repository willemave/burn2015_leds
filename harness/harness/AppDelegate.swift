import Cocoa
import OpenGL
import GLKit

@NSApplicationMain
class AppDelegate: NSObject, NSApplicationDelegate {
  @IBOutlet var newWindow: NSWindow?
  @IBOutlet var controller: BaseViewControler?

  func applicationDidFinishLaunching(aNotification: NSNotification) {
    controller = BaseViewControler()
    let content = newWindow!.contentView as NSView!
    let view = controller!.view
    content.addSubview(view)
    
    newWindow!.makeKeyAndOrderFront(nil)
    
//    // Create a timer to render.
//    timer = NSTimer(timeInterval: 1.0 / 60.0,
//                    target: self,
//                    selector: "timerFireMethod:",
//                    userInfo: nil,
//                    repeats: true)
//    NSRunLoop.currentRunLoop().addTimer(timer, forMode: NSDefaultRunLoopMode)
  }
  
  func applicationShouldTerminateAfterLastWindowClosed(sender: NSApplication) -> Bool {
    return true
  }
  
  private class func getTicks() -> UInt64 {
    var t = timeval()
    gettimeofday(&t, nil)
    return UInt64(t.tv_sec * 1000) + UInt64(t.tv_usec / 1000)
  }
}