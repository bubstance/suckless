" this file is copyright free (public domain)



" --{ autoinstall command }--
    if ! filereadable(system('echo -n "${XDG_CONFIG_HOME:-$HOME/.config}/nvim/autoload/plug.vim"'))
        echo "Downloading vim-plug to manage plugins..."
        silent !mkdir -p ${XDG_CONFIG_HOME:-$HOME/.config}/nvim/autoload/
        silent !curl "https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim" > ${XDG_CONFIG_HOME:-$HOME/.config}/nvim/autoload/plug.vim
        autocmd VimEnter * PlugInstall
    endif



" ---{ sane defaults }---
filetype plugin on " enter the 21st century
let mapleader=" "
nnoremap c "_c
syntax on

set backspace=indent,eol,start
set cindent
set clipboard^=unnamed,unnamedplus
" set colorcolumn=80
set cursorline
set cursorcolumn
set encoding=utf-8
" set expandtab
set go=a
set ignorecase
set incsearch
set lcs=tab:>-,lead:•,trail:~
set mouse=a
set nobackup
set noerrorbells
set nohlsearch
set nu rnu
set path+=**
set ruler
set scrolloff=4
set shiftwidth=4
set showtabline=2
set sidescrolloff=4
set signcolumn=yes
set smartcase
set smartindent
set spelllang=en_us
set splitbelow splitright
set tabstop=4
set title
set viewoptions=cursor,folds,slash,unix
set wildignore=*.docx,*.exe,*.flv,*.gif,*.img,*.jpg,*.odt,*.pdf,*.png,*.pyc,*.xlsx
set wildmenu
set wildmode=list,full

" allow gf to edit nonexistent files
    map gf :edit <cfile><CR>
" ex mode replaced with gq
    nnoremap Q gq
" 'replace all' aliased to S
    nnoremap S :%s//g<Left><Left>
" easily leave terminal buffer
    tnoremap <Leader><Esc> <C-\><C-n>
" delete visual selection with backspace
    xnoremap <BS> x
" perform dot commands over visual blocks
    xnoremap . :normal .<CR>
" rehighlight visual selection after indenting
    xnoremap < <gv
    xnoremap > >gv
" subtle tweaks for reading diffs
    if &diff
        highlight! link DiffText MatchPattern
    endif
" clear all trailing whitespace and newlines on save
    autocmd BufWritePre * let currPos = getpos(".")
    autocmd BufWritePre * %s/\s\+$//e
    autocmd BufWritePre * %s/\n\+\%$//e
    autocmd BufWritePre *.[ch] %s/\%$/\r/e
    autocmd BufWritePre * cal cursor(currPos[1], currPos[2])
" clear out TeX build files when closing a .tex file
    autocmd VimLeave *.tex !texclear %
" disable automatic commenting on new lines
    autocmd FileType * setlocal formatoptions-=c formatoptions -=r formatoptions-=o
" netrw tweaks (for those who don't want NERDTree)
    let g:netrw_list_hide=netrw_gitignore#Hide()
    let g:netrw_list_hide.=',\(^\|\s\s\)zs\.\S+'
    let g:netrw_banner=0       " disable horrible banner
    let g:netrw_browse_split=3 " open in prior window
    let g:netrw_altv=1         " open split to the right
    let g:netrw_liststyle=3    " tree view
" quick load/edit (n)vim configuration
    map <Leader>ve :edit $HOME/.config/nvim/init.vim<CR>
    map <Leader>vr :source $HOME/.config/nvim/init.vim<CR>
    " map <Leader>ve :edit $HOME/.vimrc<CR>
    " map <Leader>vr :source $HOME/.vimrc<CR>
" read files as desired
    let g:vimwiki_ext2syntax = {'.md': 'markdown', '.markdown': 'markdown', '.mdown': 'markdown'}
    let g:vimwiki_list = [{'path': '$HOME/.local/share/nvim/vimwiki', 'syntax': 'markdown', 'ext': '.md'}]
    autocmd BufRead,BufNewFile /tmp/calcurse*,~/.calcurse/notes/* set filetype=markdown
    autocmd BufRead,BufNewFile *.ms,*.me,*.mom,*.man set filetype=groff
    autocmd BufRead,BufNewFile *.Rmd,*.rmd set filetype=rmd
    autocmd BufRead,BufNewFile *.tex set filetype=tex
" recompile dwmblocks after updating its config.h
    autocmd BufWritePost ~/.local/src/dwmblocks/config.h !cd ~/.local/src/dwmblocks/; doas make install && { killall -q dwmblocks;setsid dwmblocks & }
" save files with elevated permissions without closing
    cnoremap w!! execute 'silent! write !doas tee % >/dev/null' <bar> edit!
    " cnoremap w!! execute 'silent! write !sudo tee % >/dev/null' <bar> edit!
" run xrdb whenever xresources or xdefaults are updated
    autocmd BufRead,BufNewFile Xresources,Xdefaults,xresources,xdefaults set filetype=xdefaults
    autocmd BufWritePost Xresources,Xdefaults,xresources,xdefaults !xrdb %



" ---{ plugins }---
call plug#begin(system('echo -n "${XDG_CONFIG_HOME:-$HOME/.config}/nvim/plugged"'))
  " for function
    Plug 'airblade/vim-gitgutter'
    Plug 'gentoo/gentoo-syntax'
    Plug 'jiangmiao/auto-pairs'
    Plug 'junegunn/fzf', { 'do': { -> fzf#install() } }
    Plug 'junegunn/fzf.vim'
    Plug 'junegunn/goyo.vim'
    " Plug 'junegunn/limelight.vim'
    Plug 'kshenoy/vim-signature'
    " Plug 'preservim/nerdtree'
    Plug 'ptzz/lf.vim'
    Plug 'tpope/vim-commentary'
    Plug 'tpope/vim-fugitive'
    Plug 'tpope/vim-sensible'
    Plug 'tpope/vim-speeddating'
    Plug 'tpope/vim-surround'
    Plug 'tpope/vim-unimpaired'
    Plug 'tpope/vim-vinegar'
    Plug 'wesQ3/vim-windowswap'
    Plug 'vim-pandoc/vim-pandoc-syntax'
    Plug 'vim-scripts/restore_view.vim'
    Plug 'vimwiki/vimwiki'
    Plug 'voldikss/vim-floaterm'
    Plug 'xolox/vim-misc'
    Plug 'xolox/vim-session'
  " for looks
	Plug 'itchyny/lightline.vim'
    Plug 'rose-pine/neovim'
call plug#end()

" --{ colors and themes}--
" required for some terminals, doesn't seem to hurt others
    let &t_8f="\<Esc>[38;2;%lu;%lu;%lum"
    let &t_8b="\<Esc>[48;2;%lu;%lu;%lum"
    set t_Co=256

" colorscheme and theme
    set background=dark
    colorscheme rose-pine

" lightline.vim
    set noshowmode
    let g:lightline = {
      \ 'colorscheme': 'rosepine',
      \ 'active': {
      \   'left': [ [ 'mode', 'paste' ], [ 'gitbranch', 'readonly', 'modified' ] ],
      \   'right': [ [ 'lineinfo' ], [ 'percent' ], [ 'filetype' ] ]
      \ },
      \ 'component_function': {
      \   'gitbranch': 'FugitiveHead'
      \ },
      \ 'tabline': {
      \   'left': [ [ 'tabs' ] ],
      \   'right': [ ]
      \ },
      \ }

" fixes sign column colors if using gitgutter
    highlight! link SignColumn LineNr
    autocmd ColorScheme * highlight! link SignColumn LineNr

" set status and tab lines to term colors
    hi StatusLine ctermbg=0 cterm=NONE
    hi TabLineFill ctermbg=0 cterm=NONE
    hi TabLine ctermbg=0 cterm=NONE
    hi TabLineSel ctermbg=0 cterm=NONE

" remove tildes from nonexistent lines
    " hi! EndOfBuffer ctermbg=0 ctermfg=0 guibg=0 guifg=0

" --{ plugin tweaks and hacks }--
" fzf customization
    let g:fzf_layout = { 'up': '~90%', 'window': { 'height': 0.8, 'width': 0.8, 'xoffset': 0.5, 'yoffset': 0.5 } }
    let $FZF_DEFAULT_OPTS = '--layout=reverse --info=inline'
    command! -bang -nargs=? -complete=dir Files
        \ call fzf#run(fzf#wrap('files', fzf#vim#with_preview({ 'dir': <q-args>, 'sink': 'e', 'source': 'rg --files --hidden' }), <bang>0))
    command! -bang -nargs=? -complete=dir AllFiles
        \ call fzf#run(fzf#wrap('allfiles', fzf#vim#with_preview({ 'dir': <q-args>, 'sink': 'e', 'source': 'rg --files --hidden --no-ignore' }), <bang>0))
    map <Leader>f :Files<CR>
    map <Leader>F :AllFiles<CR>

" NERDTree customization
    " nnoremap <expr> <Leader>n g:NERDTree.IsOpen() ? ':NERDTreeClose<CR>' : @% == '' ? ':NERDTree<CR>' : ':NERDTreeFind<CR>'
    " nmap <Leader>N :NERDTreeFind<CR>
    " autocmd BufEnter * if (winnr("$") == 1 && exists("b:NERDTree") && b:NERDTree.isTabTree()) | q | endif
    " if has('nvim')
    "     let NERDTreeBookmarksFile = stdpath('data') . '/NERDTreeBookmarks'
    " else
    "     let NERDTreeBookmarksFile = '$HOME/.config/nvim' . '/NERDTreeBookmarks'
    " endif
    " autocmd BufEnter * if bufname('#') =~ 'NERD_tree_\d\+' && bufname('%') !~ 'NERD_tree_\d\+' && winnr('$') > 1 |
    "     \ let buf=bufnr() | buffer# | execute "normal! \<C-W>w" | execute 'buffer'.buf | endif
    " let NERDTreeMinimalUI=1
    " let NERDTreeShowHidden=1
    " let g:NERDTreeDirArrowExpandable = '+'
    " let g:NERDTreeDirArrowCollapsable = '~'

" vim-session settings
    let g:session_autosave='no'
    map <Leader>ss :SaveSession<Space>
    map <Leader>sS :SaveSession!<Space>
    map <Leader>so :OpenSession<Space>
    map <Leader>sO :OpenSession!<Space>
    map <Leader>sd :DeleteSession<Space>
    map <Leader>sD :DeleteSession!<Space>
    " set sessionoptions-=buffers

" vim-floaterm bindings
    let g:floaterm_keymap_new    = '<F7>'
    let g:floaterm_keymap_prev   = '<F8>'
    let g:floaterm_keymap_next   = '<F9>'
    let g:floaterm_keymap_toggle = '<F12>'

" remap default lf.vim binding
    let g:lf_map_keys = 0
    map <Leader>r :Lf<CR>



" ---{ custom commands and functions }---
" ctags integration
    command! MakeTags !ctags -R .

" ---{ custom status line (if not using lightline.vim) }---
    " git branch in statusline
    function! GitBranch()
        return system("git rev-parse --abbrev-ref HEAD 2>/dev/null | tr -d '\n'")
    endfunction

    function! StatuslineGit()
        let l:branchname = GitBranch()
        return strlen(l:branchname) > 0?' '.l:branchname.' ':''
    endfunction

    set laststatus=2
    set statusline=
    set statusline+=%#LineNr#
    " set statusline+=\ %f
    set statusline+=%m
    set statusline+=\ %r
    set statusline+=%=
    " set statusline+=%y
    " set statusline+=\ \[%{strlen(&fenc)?&fenc:'none'}
    " set statusline+=\|%{&ff}\]
    set statusline+=\ \[\ %l:%c\ \|\ %P\ \]
    set statusline+=\ %*
    set statusline+=%{StatuslineGit()}

" ---{ mappings }---
" buffers
    map <Leader>bs :buffers<CR>:b
    map <Leader>bd :buffers<CR>:bd!
    map <Leader>bk :bd!<CR>
    map <Leader>bl :buffers<CR>
    map <Leader>bn :bn<CR>
    map <Leader>bp :bp<CR>

" compile and preview documents quickly
    map <Leader>c :w! \| !compiler "%:p"<CR>
    map <Leader>p :!opout "%:p"<CR>

" easier tabs
    nnoremap <silent><tab> :if &modifiable && !&readonly && &modified <CR> :write<CR> :endif<CR>:bn<CR>
    nnoremap <silent><S-tab> :if &modifiable && !&readonly && &modified <CR> :write<CR> :endif<CR>:bp<CR>
    map <Leader><Tab> :tabnew<CR>
    noremap <Leader>1 1gt
    noremap <Leader>2 2gt
    noremap <Leader>3 3gt
    noremap <Leader>4 4gt
    noremap <Leader>5 5gt
    noremap <Leader>6 6gt
    noremap <Leader>7 7gt
    noremap <Leader>8 8gt
    noremap <Leader>9 9gt
    noremap <Leader>0 :tablast<CR>
    noremap <Leader>[ :tabprevious<CR>
    noremap <Leader>] :tabnext<CR>

" insert mode navigation
    inoremap <C-j> <Esc>A
    inoremap <C-k> <Esc>I

" move entire chunks in visual mode
    vnoremap J :m '>+1<CR>gv=gv
    vnoremap K :m '<-2<CR>gv=gv

" random shit
    nnoremap <C-d> <C-d>zz
    nnoremap <C-u> <C-u>zz

" window movements
    map <Leader>= <C-w>=
    map <Leader>- <C-w>s
    map <Leader>\ <C-w>v
    map <Leader>x <C-w>c
    map <C-h> <C-w>h
    map <C-j> <C-w>j
    map <C-k> <C-w>k
    map <C-l> <C-w>l
    map <C-Left> <C-w>h
    map <C-Down> <C-w>j
    map <C-Up> <C-w>k
    map <C-Right> <C-w>l
