(package-initialize)
(add-to-list 'load-path "~/.emacs.d/lisp/")

(require 'init-pkgs)
(require 'init-defaults)
(require 'init-keybindings)
(require 'init-ui)


(load-theme 'spacemacs-dark t)

(defun open-init-file ()
  (interactive)
  (find-file "~/.emacs.d/init.el"))

(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(package-selected-packages
   (quote
    (popwin slime spacemacs-theme smartparens hungry-delete))))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 )
