(define-module (general utils))

(export symbol-value
        mtp
        launch
        session-name
        send)

(use-modules (general doc)
             (internal))

(defun symbol-value (s)
  (if (symbol? s)
      (primitive-eval s)
      (error "Not a symbol !")))

(defvar mtp (mainwin-qmtp (main-window)))

(defun launch (s)
  (qnet-launch-session mtp s))

(defun session-name (n)
  (if (< n (qnet-sessions-number mtp))
      (chatsession-session-name (qnet-session mtp n))
      nil))

(defun send (session mesg)
  (if (< session (qnet-sessions-number mtp))
      (chatsession-send (qnet-session mtp session) mesg)))
