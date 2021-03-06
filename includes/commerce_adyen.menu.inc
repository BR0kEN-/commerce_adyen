<?php
/**
 * @file
 * Adyen menu.
 */

/**
 * Menu route controller.
 *
 * @param string $type
 *   Type of response from Adyen.
 *
 * @see commerce_adyen_menu()
 *
 * @return string
 *   Processing result.
 */
function commerce_adyen_controller($type) {
  $response = '';

  try {
    $responses = commerce_adyen_responses();

    if (isset($responses[$type])) {
      $response = new $responses[$type]($_REQUEST);
    }
  }
  catch (\Commerce\Adyen\Exception $e) {
    $response = $e->getMessage();
    watchdog_exception(COMMERCE_ADYEN_PAYMENT_METHOD, $e);
  }

  return $response;
}

/**
 * Menu route delivery.
 *
 * @param string $response
 *   Response from callback.
 *
 * @see drupal_deliver_html_page()
 */
function commerce_adyen_deliver($response) {
  // Do not trigger complex logic of default delivery callback.
  print $response;
}
