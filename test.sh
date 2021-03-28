rm -rf randoms
touch randoms
./rand $1 >> randoms
./push_swap randoms
