(define-module (general filters))

(export filter-login
        filter-tell
        filter-warn-on-login
        filter-warn-on-tell)

(use-modules (internal)
             (general doc)
             (general utils)
             (ice-9 regex)
             (xosdguile)
             (network session))

(define existing-tabs '()) ;; TODO: fix this awful hack
(define logins '()) ;; TODO: update this list when sessions are closed

(defun filter-login (disp s)
  (let* ((pattern "^<Mtp> Welcome, (\\w+).$")
         (res (string-match pattern s)))
    (if res
      (set! logins (acons disp (match:substring res 1) logins)))))

(defun filter-tell (disp s)
  (let* ((pattern1 "^<Mtp> (\\w+) tells you:(.*)$")
         (pattern2 "^<Mtp> You tell (\\w+):(.*)$")
         (res (or (string-match pattern1 s) (string-match pattern2 s))))
    (if res
      (let ((login (match:substring res 1))
            (mylog (cdr (assoc disp logins))))
        (if (not (member login existing-tabs))
          (begin
            (set! existing-tabs (cons login existing-tabs))
            (dispatch-to-output disp `(,login #f ((,pattern1 . ,(string-append "<" login ">\\2"))
                                                  (,pattern2 . ,(string-append "<" mylog ">\\2")))))))))))

(defun filter-warn-on-login (disp s osd)
  (let ((condition (assoc disp logins)))
    (if condition
      (let* ((mylog (cdr condition))
             (pattern1 (string-append "^.*" mylog ".*$"))
             (res1 (string-match pattern1 s))
             (pattern2 (string-append "^(<" mylog ">|<Mtp> \\*" mylog " ).*$"))
             (res2 (string-match pattern2 s)))
        (if (and res1 (not res2))
          (begin
            (xosd-scroll osd 1)
            (xosd-display-string osd (- (xosd-get-number-lines osd) 1) s)))))))

(defun filter-warn-on-tell (disp s osd)
  (let ((condition (assoc disp logins)))
    (if condition
      (let* ((mylog (cdr condition))
             (pattern "^<Mtp> (\\w+) tells you:(.*)$")
             (res (string-match pattern s)))
        (if res
          (let ((msg (string-append "<" (match:substring res 1) ">" (match:substring res 2))))
            (xosd-scroll osd 1)
            (xosd-display-string osd (- (xosd-get-number-lines osd) 1) msg)))))))

(add-hook! append-hook filter-login)
