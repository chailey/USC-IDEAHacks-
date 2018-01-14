import requests, json

subscription_key = '8bbf30264bd74325bf1ca6f0df5abe11'
url = 'https://westcentralus.api.cognitive.microsoft.com/face/v1.0'

# Request headers
headers = {
    'Content-Type': 'application/json',
	'Ocp-Apim-Subscription-Key': subscription_key,
}

# Request parameters.
params = {
    'returnFaceId': 'true',
	'returnFaceLandmarks': 'false',
	'returnFaceAttributes': 'age,gender,headPose,smile,facialHair,glasses,emotion,hair,makeup,occlusion,accessories,blur,exposure,noise',
}

# Body. The URL of a JPEG image to analyze.
body = {'url': 'https://upload.wikimedia.org/wikipedia/commons/c/c3/RH_Louise_Lillian_Gish.jpg'}

def main():
	try:
	    # Execute the REST API call and get the response.
		response = requests.request('POST', url + '/face/v1.0/detect', json=body, data=None, headers=headers, params=params)
		print ('Response:')
		parsed = json.loads(response.text)
		print (json.dumps(parsed, sort_keys=True, indent=2))
	
	except Exception as e:
		print('Error:')
		print(e)

if __name__ == "__main__":
	main()
