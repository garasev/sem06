import bcrypt

# get password
password = 'password'
# encode password to bytes
password_b = bytes(password, encoding='utf-8')
# gen salt and hashed
salt = bcrypt.gensalt()
hashed = bcrypt.hashpw(password_b, salt)
# decode salt and hashed to string
salt_decode = salt.decode('utf-8')
hashed_decode = hashed.decode('utf-8')
# save into data base 'salt_decode' and 'hashed_decode'

new_password_b = password_b

# take from data base 'salt_decode' and 'hashed'
salt_encode = bytes(salt_decode, encoding='utf-8')
hashed_encode = bytes(hashed_decode, encoding='utf-8')
# hashed new password
new_hashed = bcrypt.hashpw(new_password_b, salt_encode)

# check match
if new_hashed == hashed_encode:
    print("It's matched!")
else:
    print("It Does not Match :(")
