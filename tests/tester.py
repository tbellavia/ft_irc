from http.client import ResponseNotReady
import socket
import yaml
from pprint import pprint

class TestIRC:
	BUFFSIZE = 510
	CRLF = "\r\n"
	OPER_USER = "ft_oper"
	OPER_PASS = "ft_oper"

	def __init__(self, addr, port, password):
		self.addr = addr
		self.port = port
		self.password = password
		self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

		with open("replies.yaml", "r") as f:
			replies = yaml.load(f.read(), yaml.BaseLoader)
			self.errors = replies['ERROR_REPLIES']
			self.response = replies['COMMAND_RESPONSES']

	def _connect(self):
		self.client.connect((self.addr, self.port))

	def  _disconnect(self):
		self.client.close()

	def _ston(self, msg):
		return f"{msg}{TestIRC.CRLF}".encode()

	def _recv(self):
		return self.client.recv(TestIRC.BUFFSIZE).decode().strip()

	def _send(self, msg):
		self.client.send(self._ston(msg))

	def _send_recv(self, msg):
		self._send(msg)
		return self._recv()

	def _get_arguments(self, response):
		args = {}

		splitted = response.split(" ")
		if len(splitted) < 5:
			return args
		args['code'] = splitted[1]
		args['name'] = splitted[3]
		args['message'] = response.split(":")[2].strip()
		return args

	def _check_reply(self, args):
		if len(args) != 3:
			return False
		code = args['code']
		name = args['name']
		msg = args['message']

		reply = self.errors[code]
		print(reply)

	def _wait_reponse(self):
		while True:
			response = self._recv()

			if response == "":
				print("I have been disconnected!")
				break

	def test_pass(self):
		response = self._send_recv("PASS")
		print(response)
		response = self._send_recv("PASS pass pass")
		print(response)
		self._send("PASS pass")

	
	def test_nick(self):
		self._send(f"PASS {self.password}")

		## No Nickname given
		response = self._send_recv("NICK")
		print(response)

		## Invalid Nickname
		response = self._send_recv("NICK p*u")
		print(response)

		## Good Nickname
		self._send("NICK MielPops")

		## Changing Nickname
		self._send("NICK Tony")
		print( self._send_recv("NICK Tony") )
		

	def test_user(self):
		self._send("PASS pass")
		print(self._send_recv("USER"))
		print(self._send_recv("USER a b c d e"))
		self._send("USER Tony * 0 :Tony Tony")

	def test_connection(self):
		self._send("PASS pass")
		self._send("NICK MielPops")
		self._send("USER Tony * 0 :realname")
	
	def test_oper(self):
		self._send("PASS pass")
		self._send("NICK MielPops")
		self._send("USER Tony * 0 :realname")

		def test_oper_not_enough_params():
			self._send(f"OPER {self.OPER_USER}")
			print(self._recv())

		def test_oper_pass_mismatch():
			self._send(f"OPER bad bad")
			print(self._recv())

		def test_oper_success():
			self._send(f"OPER {self.OPER_USER} {self.OPER_PASS}")
			print(self._recv())

		test_oper_not_enough_params()
		test_oper_pass_mismatch()
		test_oper_success()

	def test_join(self):
		self._send("JOIN #first,#second key1,key2")

	def launch_test(self):
		"""
			Launch all tests.

			Check Command name
			Check Reply CODE
			Check Message
		"""
		self._connect()
		# self.test_pass()
		# self.test_nick()
		# self.test_user()
		# self.test_connection()
		# self.test_oper()
		self.test_join()

		self._disconnect()

tester = TestIRC("127.0.0.1", 6697, "pass")
tester.launch_test()
