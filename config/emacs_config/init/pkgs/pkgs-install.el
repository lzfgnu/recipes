(when (>= emacs-major-version 24)
  (require 'package)
  (package-initialize)
  (setq package-archives '(("gnu"   . "http://elpa.gnu.org/packages/")
			   ("melpa" . "http://elpa.emacs-china.org/melpa/"))))
(require 'cl)
(defvar my-pkgs '(
		  ;; auto complete
		  company
		  irony
		  irony-eldoc
		  company-irony
		  company-irony-c-headers
		  flycheck
		  flycheck-irony
		  ;; buffer editor
		  hungry-delete
		  smartparens
		  popwin
		  ;; theme
		  spacemacs-theme
		  ))

(setq package-selected-packages my-pkgs)
(defun my-pkg-installedp ()
  (loop for pkg in my-pkgs
	when (not (package-installed-p pkg))
	do (return nil)
	finally (return t)))

(unless (my-pkg-installedp)
  (message "%s" "Refreshing pkg database...")
  (package-refresh-contents)
  (dolist (pkg my-pkgs)
    (when (not (package-installed-p pkg))
      (package-install pkg))))


(provide 'pkgs-install)
