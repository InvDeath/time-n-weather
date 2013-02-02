<?php
/**
 * @file
 * Callbacks for administration page forms.
 */

/**
 * Creating form for module's form.
 *
 * @ingroup forms
 * @see system_settings_form().
 */
function timenweather_admin_settings() {

  $form['cities'] = array(
    '#type'   => 'fieldset',
    '#title'  => t('Cities to observe'),
  );
  $form['cities']['city_name'] = array(
    '#type'   => 'textfield',
    '#title'  => t('City 1'),
  );
  $form['cities']['city_time'] = array(
    '#type'   => 'checkbox',
    '#title'  => t('Add clock'),
  );

  return system_settings_form($form, TRUE);
}

/**
 * Submit form function.
 */
function timenweather_admin_settings_submit($form, &$form_state) {
  $city = $form_state['values']['city_name'];
  $isTime = $form_state['values']['city_time'];

  variable_set('timenweather_settings_city', $city);
  variable_set('timenweather_settings_time', $isTime);

  return true;
}