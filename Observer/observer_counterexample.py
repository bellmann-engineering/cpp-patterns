import time
import random


class Item:
    """Represents a product item."""

    def __init__(self, name, price):
        self.name = name
        self.price = price
        self.in_stock = False

    def check_stock(self):
        return random.choice([True, False])


class Customer:
    """Represents a customer who can be interested in an item."""

    def __init__(self, name, email, phone, notify_by_email=True, notify_by_sms=False):
        self.name = name
        self.email = email
        self.phone = phone
        self.notify_by_email = notify_by_email
        self.notify_by_sms = notify_by_sms
        self.items_of_interest = []

    def is_interested(self, item):
        return item in self.items_of_interest

    def send_notification(self, item):
        message = f"{item.name} is back in stock!"
        if self.notify_by_email:
            self.send_email(message)
        if self.notify_by_sms:
            self.send_sms(message)

    def send_email(self, message):
        print(f"Email sent to {self.name} ({self.email}): {message}")

    def send_sms(self, message):
        print(f"SMS sent to {self.name} ({self.phone}): {message}")


def check_items_stock(items, customers):
    while True:
        print("Checking stock...")
        for item in items:
            in_stock = item.check_stock()
            print(f"{item.name} is now {'in stock' if in_stock else 'out of stock'}.")
            if in_stock and not item.in_stock:
                for customer in customers:
                    if customer.is_interested(item):
                        customer.send_notification(item)
            item.in_stock = in_stock

        time.sleep(5)
        print()


if __name__ == "__main__":
    lenovo_notebook = Item("Lenovo Notebook", 500.0)
    hp_computer = Item("HP Computer", 400.0)

    all_items = [lenovo_notebook, hp_computer]

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

    all_customers = [alice, bob, charlie]

    alice.items_of_interest = [lenovo_notebook]
    bob.items_of_interest = [lenovo_notebook]
    charlie.items_of_interest = [hp_computer]

    check_items_stock(all_items, all_customers)
