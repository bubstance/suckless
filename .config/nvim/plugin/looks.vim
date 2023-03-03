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
      \ 'colorscheme': 'rosepine_custom',
      \ 'active': {
      \   'left': [ [ 'mode', 'paste' ], [ 'gitbranch', 'readonly', 'modified' ] ],
      \   'right': [ [ 'lineinfo' ], [ 'percent' ], [ 'filetype' ] ]
      \ },
      \ 'component_function': {
      \   'gitbranch': 'FugitiveHead',
      \   'readonly': 'LightlineReadonly',
      \ },
      \ 'tab_component_function': {
      \   'tabnum': ''
      \ },
      \ 'tabline': {
      \   'left': [ [ 'tabs' ] ],
      \   'right': [ ]
      \ },
      \ }

    function! LightlineReadonly()
      return &readonly && &filetype !=# 'help' ? 'RO' : ''
    endfunction

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



" ---{ custom status line (if not using lightline.vim) }---
" -----{ note: git branch works while *in* directory }-----
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
    set statusline+=\ %*
    set statusline+=%{StatuslineGit()}
    set statusline+=%#LineNr#
    " set statusline+=\ %f
    set statusline+=%m
    set statusline+=\ %r
    set statusline+=%=
    " set statusline+=%y
    " set statusline+=\ \[%{strlen(&fenc)?&fenc:'none'}
    " set statusline+=\|%{&ff}\]
    set statusline+=\ \[\ %l:%c\ \|\ %P\ \]
