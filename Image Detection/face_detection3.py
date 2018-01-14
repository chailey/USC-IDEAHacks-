""" Python 3.6 script that opens a locally stored image file and 
passes the binary to the Microsoft Face API for image detection analysis and displays the json response """

import RPi.GPIO as GPIO
import io
import picamera
import time
import requests
import json
from PIL import Image, ImageDraw

uri_base = 'https://westcentralus.api.cognitive.microsoft.com'
subscription_key = '8bbf30264bd74325bf1ca6f0df5abe11'

# Request headers
# for locally stored image files use
# 'Content-Type': 'application/octet-stream'
headers_local = {
     'Content-Type': 'application/octet-stream',
     'Ocp-Apim-Subscription-Key': subscription_key,
}
headers_json = {
    'Content-Type': 'application/json',
     'Ocp-Apim-Subscription-Key': subscription_key,
}

# Request parameters 
# The detection options for MCS Face API check MCS face api 
# documentation for complete list of features available for githu
# detection in an image
# these parameters tell the api I want to detect a face and a smile


# route to the face api
path_to_face_api = '/face/v1.0/detect'
path_to_person_group = '/face/v1.0/persongroups/my_friends'
path_to_list_person_groups = '/face/v1.0/persongroups'
path_to_list_persons = '/face/v1.0/persongroups/my_friends/persons'
path_to_create_person = '/face/v1.0/persongroups/my_friends/persons'

id = '24f87bd1-7e87-4398-b7e9-be6aea1b3379'

#Convert width height to a point in a rectangle
def getRectangle(faceDictionary):
    rect = faceDictionary['faceRectangle']
    left = rect['left']
    top = rect['top']
    bottom = left + rect['height']
    right = top + rect['width']
    return ((left, top), (bottom, right))

def persongroups():
    params = {'personGroupId': 'my_friends'}
    body = {"name": "my_friends"}
    try:
        response = requests.put(uri_base+path_to_person_group,
                                data=json.dumps(body), 
                                headers=headers_json,
                                params=params)
        print ('Response:')
        print(response)
        parsed = response.json()
        print(parsed)

    except Exception as e:
        print('Error:')
        print(e)

def list_persongroups():
    try:
        response = requests.get(uri_base+path_to_list_person_groups,
                                headers=headers_json)
        
        print ('Response:')
        parsed = response.json()
        print(parsed)
    
    except Exception as e:
        print('Error:')
        print(e)

def list_persons():
    try:
        response = requests.get(uri_base+path_to_list_persons,
                                headers=headers_json)
        
        print ('Response:')
        parsed = response.json()
        print(parsed)
    
    except Exception as e:
        print('Error:')
        print(e)

def delete_person(id):
    path_to_delete_persons = '/face/v1.0/persongroups/my_friends/persons/{}'.format(id)
    params = {
        'personGroupId': 'my_friends',
        'personId': id
    }
    try:
        response = requests.delete(uri_base+path_to_delete_persons,
                                headers=headers_json)
        
        print ('Response:')
        parsed = response.json()
        print(parsed)
    
    except Exception as e:
        print('Error:')
        print(e)

def create_person():
    # person-Id: 24f87bd1-7e87-4398-b7e9-be6aea1b3379

    params = {'personGroupId': 'my_friends'}
    body = {"name": "Joel"}
    
    try:
        response = requests.post(uri_base+path_to_create_person,
                                data=json.dumps(body), 
                                headers=headers_json,
                                params=params)
        print ('Response:')
        # print(response)
        parsed = response.json()
        print(parsed)
        return parsed['personId']


    except Exception as e:
        print('Error:')
        print(e)

def upload_image(file, id):
    path_to_upload_face = '/face/v1.0/persongroups/my_friends/persons/{}/persistedFaces'.format(id)

    params = {
        'personGroupId': 'my_friends',
        'personId': id # Joel
    }

    with open(file, 'rb') as pic:
            img_data_joel = pic.read()
            #print(img_data_joel)

    try:
        response = requests.post(uri_base+path_to_upload_face,
                                data=img_data_joel, 
                                headers=headers_local,
                                params=params)
        print ('Response:')
        print(response)
        parsed = response.json()
        print(parsed)

        img = Image.open(file)
        draw = ImageDraw.Draw(img)
        # for face in parsed:
        #     draw.rectangle(getRectangle(face), outline='red')
        img.show()

    except Exception as e:
        print('Error:')
        print(e)

def train_model():
    path_to_train = '/face/v1.0/persongroups/my_friends/train'

    params = {
        'personGroupId': 'my_friends'
    }

    try:
        response = requests.post(uri_base+path_to_train,
                                headers=headers_json,
                                params=params)
        print ('Response:')
        print(response)
        # parsed = response.json()
        # print(parsed)

    except Exception as e:
        print('Error:')
        print(e)

def main(filename):
    path_to_id = '/face/v1.0/identify'

    params = {
        'returnFaceId': 'true',
        'returnFaceAttributes': 'age,gender,headPose,smile,facialHair,glasses,emotion,hair,makeup,occlusion,accessories,blur,exposure,noise',
    }

    with open(filename, 'rb') as f:
        img_data = f.read()
    try:
        # Execute the api call as a POST request. 
        # What's happening?: You're sending the data, headers and
        # parameter to the api route & saving the
        # mcs server's response to a variable.
        # Note: mcs face api only returns 1 analysis at time
        response = requests.post(uri_base + path_to_face_api,
                                 data=img_data, 
                                 headers=headers_local,
                                 params=params, 
				 verify=False)
        
        print ('Response:')
        # json() is a method from the request library that converts 
        # the json reponse to a python friendly data structure
        parsed = response.json()
            
        # display the image analysis data
        print (parsed)
        #img = Image.open(filename)
        #draw = ImageDraw.Draw(img)
        #print(parsed['faceRectangle'])
        #for face in parsed:
        #    draw.rectangle(getRectangle(face), outline='red')
        #img.show()
        if(not parsed):
            print('no faces detected')
            GPIO.output(2, GPIO.LOW) 
            return True
        faceids = [parsed[0]['faceId']]
        print(faceids)
        params = {'personGroupId': 'my_friends'}
        body = {
            'faceIds': faceids,
            'personGroupId': 'my_friends',
        }

        response2 = requests.post(uri_base + path_to_id,
                                data=json.dumps(body),
                                headers=headers_json,
                                params=params, 
				verify=False)
        print(response2)
        parsed2 = response2.json()
        print(parsed2)
        if(parsed2[0]['candidates']):
            if(parsed2[0]['candidates'][0]['personId'] == id):
                print('This is Joel')
                GPIO.output(2, GPIO.HIGH)
                #time.sleep(0.5)
                return True
        else:
            print('this is not Joel')
            GPIO.output(2, GPIO.LOW)
            return True
    except Exception as e:
        print('Error:')
        print(e)

##############


# list_persongroups()
# id = create_person()
# upload_image('Joel/joel5.jpg', id)
# list_persons()
# delete_person('47fa4385-967e-4ac8-923d-a0a867fb66ad')
#list_persons()
# train_model()
my_stream = io.BytesIO()
GPIO.setmode(GPIO.BCM)
GPIO.setup(2, GPIO.OUT)
GPIO.output(2, GPIO.LOW) 
try:
	while(1):
		#GPIO.output(2, GPIO.LOW)
		with picamera.PiCamera() as camera:
			print("Capturing image!")
			time.sleep(1)
			camera.capture('image.jpg')
			main('image.jpg')
		time.sleep(1)
except KeyboardInterrupt:
	print("Interrupted!") 
