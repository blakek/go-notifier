#include <CoreFoundation/CoreFoundation.h>
#include <objc/objc-runtime.h>

CFStringRef makeCFString(char *cString)
{
  return CFStringCreateWithCString(kCFAllocatorDefault, cString,
                                   kCFStringEncodingUTF8);
}

void setIcon()
{
  class_replaceMethod(objc_getClass("NSBundle"),
                      sel_registerName("bundleIdentifier"),
                      method_getImplementation(
                          (Method) ^ { return CFSTR("com.apple.Terminal"); }),
                      NULL);
}

void sendNotification(char *title, char *subtitle, char *message, char *imagePath)
{
  Class bundle = objc_getClass("NSBundle");

  setIcon();

  void *(*callMethod)(id, SEL) = (void *(*)(id, SEL))objc_msgSend;
  void *(*alloc)(id, SEL, SEL) = (void *(*)(id, SEL, SEL))objc_msgSend;

  void *(*setTextValue)(id, SEL, CFStringRef) =
      (void *(*)(id, SEL, CFStringRef))objc_msgSend;

  void *(*setBooleanValue)(id, SEL, Boolean) =
      (void *(*)(id, SEL, Boolean))objc_msgSend;

  void *(*setObjectValue)(id, SEL, id) = (void *(*)(id, SEL, id))objc_msgSend;

  id notificationCenter =
      (id)callMethod((id)objc_getClass("NSUserNotificationCenter"),
                     sel_registerName("defaultUserNotificationCenter"));

  id systemNotification =
      (id)alloc((id)objc_getClass("NSUserNotification"),
                sel_registerName("alloc"), sel_registerName("init"));

  if (title != NULL)
  {
    setTextValue(systemNotification, sel_registerName("setTitle:"),
                 makeCFString(title));
  }

  if (subtitle != NULL)
  {
    setTextValue(systemNotification, sel_registerName("setSubtitle:"),
                 makeCFString(subtitle));
  }

  if (message != NULL)
  {
    setTextValue(systemNotification,
                 sel_registerName("setInformativeText:"),
                 makeCFString(message));
  }

  if (imagePath != NULL)
  {
    fputs("WARN: Adding an image is not yet implemented.\n", stderr);
  }

  setBooleanValue(systemNotification, sel_registerName("setHasActionButton:"),
                  true);

  setTextValue(systemNotification, sel_registerName("setActionButtonTitle:"),
               CFSTR("Close"));

  setObjectValue(notificationCenter, sel_registerName("deliverNotification:"),
                 systemNotification);
}
