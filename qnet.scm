(set! %load-path (append %load-path (list (string-append (getenv "HOME") "/.qnet/lisp"))))

(use-modules (general doc)
             (general font-lock)
             (general utils)
             (internal))

(add-hook! chatsession-created-hook font-lock)

; (defvar blue-face '("arial" . "blue"))
; (defvar yellow-face '("verdana" . "yellow"))
; (defvar red-face '("times" . "red"))

; (defvar block-face '("monospace" . "black"))
; (defvar server-face '("verdana" . "blue"))
; (defvar me-face '("verdana" . "darkblue"))
; (defvar other-face '("verdana" . "pink"))
; (defvar emote-face '("verdana" . "green"))
; (defvar tome-face '("verdana" . "red"))
; (defvar default-face '("verdana" . "black"))
; (defvar url-face '("verdana" . "orange"))

(set! font-lock-default-size 10)

(defface emote-face #:family "verdana" #:color "green" #:weight 75)

(font-lock-add-keywords '(("Emacs" ((0 . emote-face)
                                    ))))

; (font-lock-add-blocks '(
;                         ;; Wall
;                         (("^<Mtp> Wall :" ((0 . block-face)))
;                          ("^.*" ((0 . block-face)))
;                          ("^<Mtp> End of Wall :" ((0 . block-face))))
;                         ;; Msg
;                         (("^<Mtp> Your message" ((0 . other-face)))
;                          ("^.*" ((0 . default-face)))
;                          ("^<Mtp> You have" ((0 . me-face))))
;                         ;; Who
;                         (("^ Login .*" ((0 . block-face)))
;                          ("^.*" ((0 . block-face)))
;                          ("^(<Mtp> .*)" ((1 . server-face))))
;                         ;; Info
;                         (("^(<Mtp> History.*|<Mtp> System.*|<Mtp> Help.*)" ((0 . block-face)))
;                          ("^.*" ((0 . block-face)))
;                          ("^<.*" ((0 . block-face))))
;                         ))

(defun plip ()
  (chat-page-toggle-user-box (chatsession-chatpage (qnet-session mtp 0))))
