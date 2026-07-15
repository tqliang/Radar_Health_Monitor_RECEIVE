"""
Fetch the full certificate chain for Tencent Cloud COS.
Downloads intermediate CA and root CA from GlobalSign.
"""
import ssl
import socket
import base64
import urllib.request

hostname = "otademo-1452689283.cos.ap-guangzhou.myqcloud.com"
output_path = r"d:\ESPIDF_project\OTA_DEMO\server_certs\ca_cert.pem"

# Step 1: Get server certificate
print(f"Connecting to {hostname}...")
ctx = ssl.create_default_context()
s = ctx.wrap_socket(socket.socket(), server_hostname=hostname)
s.settimeout(10)
s.connect((hostname, 443))
cert_der = s.getpeercert(binary_form=True)
s.close()
print(f"  Server cert: {len(cert_der)} bytes")

# Step 2: Download intermediate CA
intermediate_url = "http://secure.globalsign.com/cacert/gsatlasr3ovtlsca2026q1.crt"
print(f"Downloading intermediate CA: {intermediate_url}")
response = urllib.request.urlopen(intermediate_url, timeout=10)
intermediate_der = response.read()
print(f"  Intermediate CA: {len(intermediate_der)} bytes")

# Step 3: Download GlobalSign Root R3
root_url = "http://secure.globalsign.com/cacert/root-r3.crt"
print(f"Downloading root CA: {root_url}")
response = urllib.request.urlopen(root_url, timeout=10)
root_der = response.read()
print(f"  Root CA: {len(root_der)} bytes")

# Step 4: Write all to PEM
def der_to_pem(der_bytes):
    b64 = base64.b64encode(der_bytes).decode()
    formatted = "\n".join(b64[i:i+64] for i in range(0, len(b64), 64))
    return "-----BEGIN CERTIFICATE-----\n" + formatted + "\n-----END CERTIFICATE-----\n"

with open(output_path, "w") as f:
    f.write(der_to_pem(cert_der))
    f.write(der_to_pem(intermediate_der))
    f.write(der_to_pem(root_der))

print(f"\nSaved 3 certificates to {output_path}")
print("Chain: Server -> GlobalSign Atlas R3 -> GlobalSign Root R3")