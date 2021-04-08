from django.db import models


# Create your models here.
class User(models.Model):
    first_name = models.CharField(max_length=64, default=None)
    last_name = models.CharField(max_length=64, default=None)
    second_name = models.CharField(max_length=64, default=None)
    email = models.CharField(max_length=64, default=None)
    hash = models.CharField(max_length=255, default=None)
    salt = models.CharField(max_length=255, default=None)
    finance = models.FloatField(default=0)