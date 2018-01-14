import requests

with open('melanie_person.jpg', 'rb') as pic:
	header = {'Authorization': '9025ee5b6e9d0e4'}
	params = {'image': pic}
