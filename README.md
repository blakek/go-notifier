# go-notifier

Cross platform system notifications in go (golang).

## Platforms

For macOS, this uses `NSUserNotificationCenter` APIs from cgo. This only supports macOS 10.9 and above.

For Windows, this uses [toaster](https://github.com/nels-o/toaster). This only supports Windows 8 and above.

For Linux, this uses [notify-send](http://man.cx/notify-send).

## Install

```sh
go install github.com/blakek/go-notifier
```

## Changes from `keybase/go-notifier`

This removes some functionality, but also doesn't have some of the issues.

**Fixes:**

- fixes an issue where clicking the notification would exit your Go command
- removes printing to stdout that couldn't be captured
- removes the need for a timeout on macOS. Note, make sure to not exit before the notification shows (or it won't show!)

**Lacking features:**

- removes functionality for action buttons, an image, and a custom icon (shows the Terminal icon)
