(define-module (network session))

(export define-session
        launch-session
        dispatch-to-output
        default-host
        default-port
        default-login
        default-passwd
        default-proto
        default-output
        append-hook
        )

(use-modules (internal)
             (general doc)
             (general utils)
             (ice-9 optargs))

(defvar default-host "localhost" "Default host for new sessions")
(defvar default-port 4000 "Default port for new sessions")
(defvar default-login #f "Default login for new sessions")
(defvar default-passwd #f "Default password for new sessions")
(defvar default-proto 'mtp "Default protocol for new sessions")
(defvar default-output '() "Default outputs for new sessions")

(defvar append-hook (make-hook 2))

(define complete-match "\\0")

(defmacro* define-session (name #:key (host default-host)
                                (port default-port)
                                (login default-login)
                                (passwd default-passwd)
                                (proto default-proto)
                                (output default-output))
  `(defvar ,name (list ,host ,port ,login ,passwd ',proto ,output)))

(defun dispatch-to-output (disp out)
  "Connect DISP to the new output OUT, which is described by one
of the following format:

- NAME : a default session, displaying everything with the name
NAME

- (NAME DEFAULT FILTERS) : a session with the name
NAME. DEFAULT is a boolean that sets the default behavior (#t for
accepting by default, #f for rejecting). FILTERS is a list that
sets what is contrary to the default behavior.

Each filter has one of the following formats:

- REGEXP : matches a line by REGEXP and prints it as is

- (REGEXP . RESULT) : matches a line by REGEXP and prints it as
RESULT. Backward references are available via \\0, \\1 ... \\9.

- (BEGIN END) : defines a block, where BEGIN and END are of one
of the previous formats and represent a regexp for the first and
last line of the block

- (BEGIN END MIDDLE) : same as above, except that the lines in
the middle of the block are explicitely matched. It is useful if
one wants to modify the output for a middle line.

Note: when a regexp is omitted (as MIDDLE), it is supposed to be
\"^.*$\". When a format is omitted, it is replaced by \"\\0\"
"
  (let ((ed (new-mtparea)) ;; TODO: allow multiple types of areas
        (ft (main-window-get-floating-tab (mw))))
    (if (pair? out)
      (let ((name (car out))
            (def (cadr out))
            (except (nth 2 out)))
        (interaction-area-set-display-by-default ed def)
        (let ((add-function (if def interaction-area-add-negative-filter
                                interaction-area-add-positive-filter))
              (aux (lambda (x) (if (pair? x) (list (car x) (cdr x))
                                   (list x complete-match))))
              (args (list ed)))
          (map (lambda (filter)
                 (if (pair? filter)
                   (if (string? (cdr filter))
                     (add-function ed (car filter) (cdr filter))
                     (begin
                       (set! args (append args (aux (nth 0 filter)) (aux (nth 1 filter))))
                       (if (>= (length filter) 3)
                         (set! args (append args (aux (nth 2 filter)))))
                       (apply add-function args)
                       )
                     )
                   (add-function ed filter)))
               except))
        (floating-tab-add-tab ft ed name)
        (dispatcher-add-interaction-area disp ed))
      (begin
        (floating-tab-add-tab ft ed out)
        (dispatcher-add-interaction-area disp ed)))))

(defun launch-session (session) ;; TODO: virtualize the occurences of `mtp'
  "Launch a session as defined by `define-session'"
  (let* ((host (nth 0 session))
         (port (nth 1 session))
         (login (nth 2 session))
         (passwd (nth 3 session))
         (proto (nth 4 session))
         (output (nth 5 session))
         (sock (new-mtpsocket))
         (mtp (new-mtpprotocol))
         (disp (new-dispatcher mtp))
         (proto-func (symbol-prefix-proc proto)))

    (add-hook! (dispatcher-get-internal-append-hook disp)
              (lambda (str)
                (run-hook append-hook disp str)))

    (mtpsocket-set-host sock host)
    (mtpsocket-set-port sock port)
    (if login
      (mtpsocket-set-login sock login))
    (if passwd
      (mtpsocket-set-passwd sock passwd))

    (primitive-eval (list (apply proto-func 'protocol-install-io '()) mtp sock))

    (map (lambda (out)
           (dispatch-to-output disp out))
         output)

    (mtpsocket-connet-to-host sock))

)