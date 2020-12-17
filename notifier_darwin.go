// Copyright 2016 Keybase, Inc. All rights reserved. Use of
// this source code is governed by the included BSD license.

package notifier

/*
#cgo LDFLAGS: -framework Foundation
#include "notifier_darwin.h"
extern void sendNotification(char *title, char *subtitle, char *message, char *imagePath);
*/
import "C"

type darwinNotifier struct{}

// NewNotifier constructs notifier for Windows
func NewNotifier() (Notifier, error) {
	return &darwinNotifier{}, nil
}

// DeliverNotification sends a notification
func (n darwinNotifier) DeliverNotification(notification Notification) error {
	C.sendNotification(
		C.CString(notification.Title),
		nil,
		C.CString(notification.Message),
		nil,
	)

	return nil
}
