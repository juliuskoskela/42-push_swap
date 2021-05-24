rm -rf commands
rm -rf randoms
./rand $1 >> randoms
./push_swap randoms >> commands
./checker randoms commands
