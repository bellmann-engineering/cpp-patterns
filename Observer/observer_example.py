from typing import List
from abc import ABC, abstractmethod
import random
import time


class Subject(ABC):
    """
    The Subject interface declares a set of methods for managing subscribers.
    """

    def __init__(self):
        self._observers: List[Observer] = []

    def register(self, observer: "Observer"):
        """
        Attach an observer to the subject.
        """
        if observer not in self._observers:
            self._observers.append(observer)

    def unregister(self, observer: "Observer"):
        """
        Detach an observer from the subject.
        """
        if observer in self._observers:
            self._observers.remove(observer)

    def notify(self, *args, **kwargs):
        """
        Notify all observers about an event.
        """
        for observer in self._observers:
            observer.update(self)


class Observer(ABC):
    """
    The Observer interface declares the update method, used by subjects.
    """

    @abstractmethod
    def update(self, subject, *args, **kwargs):
        """
        Receive update from subject.
        """
        raise NotImplementedError(
            "Abstract method update() must be implemented in subclasses."
        )


class Item(Subject):
    """
    Represents a product item.
    """

    def __init__(self, name: str, price: float, in_stock: bool = False):
        super().__init__()
        self.name = name
        self.price = price
        self._in_stock = in_stock

    @property
    def in_stock(self) -> bool:
        """
        Get the current stock status of the item.
        """
        return self._in_stock

    @in_stock.setter
    def in_stock(self, value: bool):
        """
        Set the current stock status of the item.
        """
        # notify should only be called if the value has changed from false to true
        if self._in_stock != value:
            self._in_stock = value
            print(
                f"{item.name} is now {'in stock' if self._in_stock else 'out of stock'}."
            )
            self.notify()


class Customer(Observer):
    """
    Represents a customer who is interested in a particular item.
    """

    def __init__(
        self,
        name: str,
        email: str,
        phone: str,
        notify_by_email: bool = True,
        notify_by_sms: bool = False,
    ):
        self.name = name
        self.email = email
        self.phone = phone
        self.notify_by_email = notify_by_email
        self.notify_by_sms = notify_by_sms

    def update(self, item: Item):
        """
        Receive update from the item.
        """
        if item.in_stock:
            message = f"{item.name} is back in stock!"
            if self.notify_by_email:
                self.send_email(message)
            if self.notify_by_sms:
                self.send_sms(message)

    def send_email(self, message: str):
        """
        Send an email notification to the customer.
        """
        # Code to send email to the customer
        print(f"Email sent to {self.name} ({self.email}): {message}")

    def send_sms(self, message: str):
        """
        Send a text message notification to the customer.
        """
        # Code to send text message to the customer
        print(f"SMS sent to {self.name} ({self.phone}): {message}")


if __name__ == "__main__":
    lenovo_notebook = Item("Lenovo Noteobok", 500.0)
    hp_pc = Item("HP Computer", 400.0)

    items = [lenovo_notebook, hp_pc]

    alice = Customer(
        "Alice",
        "alice@example.com",
        "123-456-7890",
        notify_by_email=True,
        notify_by_sms=False,
    )
    bob = Customer(
        "Bob",
        "bob@example.com",
        "234-567-8901",
        notify_by_email=False,
        notify_by_sms=True,
    )
    charlie = Customer(
        "Charlie",
        "charlie@example.com",
        "345-678-9012",
        notify_by_email=True,
        notify_by_sms=True,
    )

    lenovo_notebook.register(alice)
    lenovo_notebook.register(bob)
    hp_pc.register(charlie)

    while True:
        print("Updating stock status...")
        for item in items:
            item.in_stock = random.choice([True, False])
        time.sleep(5)
        print()
