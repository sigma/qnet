(define-module (modes mtp-browser))

(use-modules (general doc)
             (general font-lock)
             (general utils)
             (internal))

(export mtp-browser-font-lock
        block-face
        server-face
        me-face
        other-face
        emote-face
        tome-face
        url-face)

(defface block-face #:family "monospace" #:color "black")
(defface server-face #:family "verdana" #:color "blue" #:italic #t)
(defface me-face #:family "verdana" #:color "darkblue" #:weight bold)
(defface other-face #:family "verdana" #:color "pink")
(defface emote-face #:family "verdana" #:color "green")
(defface tome-face #:family "verdana" #:color "red")
(defface url-face #:family "verdana" #:color "orange")

(defvar mtp-browser-font-lock (mode-get-font-lock (mode-get-mode "MtpBrowser")))

(font-lock-add-keywords mtp-browser-font-lock
                        '(
                          ("^<Mtp>.*"
                           ((0 . server-face)))
                          ("^<Mtp> \\*.*"
                           ((0 . emote-face)))
                          ("^<Mtp> You.*"
                           ((0 . other-face)))
                          ))

(font-lock-add-blocks mtp-browser-font-lock
                      '(
                        ;; Wall
                        (("^<Mtp> Wall :" ((0 . block-face)))
                         ("^.*" ((0 . block-face)))
                         ("^<Mtp> End of Wall :" ((0 . block-face))))
                        ;; Msg
                        (("^<Mtp> Your message" ((0 . other-face)))
                         ("^.*" ((0 . default-face)))
                         ("^<Mtp> You have" ((0 . me-face))))
                        ;; Who
                        (("^ Login .*" ((0 . block-face)))
                         ("^.*" ((0 . block-face)))
                         ("^(<Mtp> .*)" ((1 . server-face))))
                        ;; Info
                        (("^(<Mtp> History.*|<Mtp> System.*|<Mtp> Help.*|Welcome to.*)" ((0 . block-face)))
                         ("^.*" ((0 . block-face)))
                         ("^<.*" ((0 . server-face))))
                        ))

(font-lock-install mtp-browser-font-lock)
